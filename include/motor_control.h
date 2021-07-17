void PumpON_command()
{
    if (value <= 90)
    {
        MotorState = true;
        EEPROM.write(motorState_mem, 1);
    }
}

void PumpOFF_command()
{
    MotorState = false;
    EEPROM.write(motorState_mem, 0);
}

void motor_on()
{
    tone(buzz, 4500, 500);
    digitalWrite(led, HIGH);
    switch (STATOR_TYPE)
    {
    case 1: //Normal Mode
        digitalWrite(Relay_ON, HIGH);
        break;
    case 2: //stator type
        digitalWrite(Relay_ON, HIGH);
        delay(on_delay);
        digitalWrite(Relay_ON, LOW);
        break;
    case 3: //CapacitorRun Mode
        digitalWrite(Relay_ON, HIGH);
        delay(1500);
        digitalWrite(Relay_ON, LOW);
        break;
    };
}

void motor_off()
{
    switch (STATOR_TYPE)
    {
    case 1: //Normal Mode
        digitalWrite(Relay_ON, LOW);
        break;
    case 2: //stator type
        digitalWrite(Relay_OFF, HIGH);
        delay(off_delay);
        digitalWrite(Relay_OFF, LOW);
        break;
    case 3: //CapacitorRun Mode
        digitalWrite(Relay_OFF, HIGH);
        delay(1500);
        digitalWrite(Relay_OFF, LOW);
        break;
    }
}

#if DryRun
void DRY_RUN_CHECK()
{
    if (dryRun_LastDistance <= Distance)
    {
        Serial.println("Dry run");
        DryRunState = true;
        errorCountState = true;
    }
    else if (dryRun_LastDistance > (Distance + 2))
    {
        Serial.println("all ok");
        dryRun_LastDistance = Distance;
        EEPROM.write(dryRun_LastDistance_mem, dryRun_LastDistance);
    }
}
#endif
