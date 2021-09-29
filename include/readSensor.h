void readSensor()
{
#if sonar
   Distance = Sonar.read();
   if (Distance <= MaxDistance && Distance >= MinDistance)
   {
      mySensor.add(Distance);
      DistanceX = mySensor.get();
      uint8_t valueX = map(DistanceX, MinDistance, MaxDistance, 100, 0);
      value = valueX;
   }
   else if (Distance >= MaxDistance)
   {
      value = 0;
   }
   else if (Distance <= MinDistance)
   {
      value = 100;
   }
   if (Distance == 0 || Distance >= MaxDistance + 10) //if Error
   {
      errorCount++;
      if (errorCount > 20)
      {
         errorCountState = true;
         errorCount = 1;
      }
   }
//    else
//    {
//       okCount++;
//       if (okCount >= 100)
//       {
//          errorCount = 0;
//          errorCountState = false;
//          okCount = 0;
//       }
// #if DryRun
//       if (DryRunState == false)
//          errorCountState = false;
// #endif
//    }
#else
   do
   {
      for (int i = 0; i < 4; i++)
      {
         data[i] = sensorSerial.read();
      }
   } while (sensorSerial.read() == 0xff);
   sensorSerial.flush();
   if (data[0] == 0xff)
   {
      int sum;
      sum = (data[0] + data[1] + data[2]) & 0x00FF;
      if (sum == data[3])
      {
         Distance = (data[1] << 8) + data[2];
         if (Distance > 30)
         {
            Distance /= 10;
            if (Distance <= MaxDistance && Distance >= MinDistance)
            {
               mySensor.add(Distance);
               DistanceX = mySensor.get();
               uint8_t valueX = map(DistanceX, MinDistance, MaxDistance, 100, 0);
               value = valueX;
            }
            else if (DistanceX >= MaxDistance)
            {
               value = 0;
            }
            else if (DistanceX <= MinDistance)
            {
               value = 100;
            }
            errorCount = 0;
            if (DryRunState == false)
               errorCountState = false;
         }
         else
         {
            debugln("Below the lower limit");
            errorCount++;
            if (errorCount > 20)
            {
               errorCountState = true;
               errorCount = 1;
            }
         }
      }
      else // if errors
      {
         errorCount++;
         if (errorCount > 20)
         {
            errorCountState = true;
            errorCount = 1;
         }
      }
   }
#endif
   if (value < 0)
   {
      value = 0;
   }
   else if (value > 100)
   {
      value = 100;
   }
   if (value <= MotorStartThreshold && ManualOff == false && AutoMode == true && Distance != 0 && value <= 90)
   {
      PumpON_command();
   }
   else if (Distance < MinDistance && Distance != 0)
   {
      PumpOFF_command();
   }
}