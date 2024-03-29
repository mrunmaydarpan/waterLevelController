void readSensor()
{
#if sonar
   Distance = Sonar.read();
   if (Distance <= MaxDistance && Distance >= MinDistance)
   {
      mySensor.add(Distance);
      DistanceX = mySensor.get();
      uint8_t valueX = map(DistanceX, MinDistance, MaxDistance, 100, 0);
#if level_5
      value = map(valueX, 0, 100, 0, 20) * 5;
#else
      value = valueX;
#endif
   }
   else if (DistanceX >= MaxDistance)
   {
      value = 0;
   }
   else if (DistanceX <= MinDistance)
   {
      value = 100;
   }
   if (Distance == 0 || DistanceX >= MaxDistance + 10) //if Error
   {
      errorCount++;
      if (errorCount > 5)
      {
         errorCountState = true;
         errorCount = 1;
      }
   }
   // else
   // {
   //    errorCount = 0;
   //    if (DryRunState == false)
   //       errorCountState = false;
   // }
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
#if level_5
               value = map(valueX, 0, 100, 0, 20) * 5;
#else
               value = valueX;
#endif
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
            Serial.println("Below the lower limit");
            errorCount++;
            if (errorCount > 5)
            {
               errorCountState = true;
               errorCount = 1;
            }
         }
      }
      else // if errors
      {
         errorCount++;
         if (errorCount > 5)
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