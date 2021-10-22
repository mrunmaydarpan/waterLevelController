void PumpON_command()
{
    if (value <= 100)
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
void RelayOFF()
{
    digitalWrite(Relay_OFF, LOW);
}

void lcd_off()
{
#if LCD_BL_OFF
    lcd.noBacklight();
#endif
}
void motor_on()
{
    switch (STATOR_TYPE)
    {
    case 1: // Normal Mode
        digitalWrite(Relay_ON, HIGH);
        break;
    case 2: // stator type
        digitalWrite(Relay_ON, HIGH);
        digitalWrite(Relay_ON_2, HIGH);
        delay(on_delay);
        digitalWrite(Relay_ON, LOW);
        delay(200);
        digitalWrite(Relay_ON_2, LOW);
        break;
    case 3: // CapacitorRun Mode
        digitalWrite(Relay_ON, HIGH);
        delay(1500);
        digitalWrite(Relay_ON, LOW);
        break;
    };
    Buzz(buzz, HIGH);
    digitalWrite(led, HIGH);
    delay(300);
    Buzz(buzz, LOW);
    lcd.backlight();
}

void motor_off()
{
    switch (STATOR_TYPE)
    {
    case 1: // Normal Mode
        digitalWrite(Relay_ON, LOW);
        break;
    case 2: // stator type
        digitalWrite(Relay_OFF, HIGH);
        RELAY_OFF = t.after(1000, RelayOFF);
        // delay(off_delay);
        // digitalWrite(Relay_OFF, LOW);
        debug("motor off test");
        break;
    case 3: // CapacitorRun Mode
        digitalWrite(Relay_OFF, HIGH);
        delay(1500);
        digitalWrite(Relay_OFF, LOW);
        break;
    }
    Buzz(buzz, HIGH);
    delay(300);
    Buzz(buzz, LOW);
    digitalWrite(led, LOW);
#if LCD_BL_OFF
    LCD_t = t.after(2000, lcd_off);
#endif
}

#if DryRun
void DRY_RUN_CHECK()
{
    if (dryRun_LastDistance <= Distance)
    {
        debugln("Dry run");
        DryRunState = true;
        errorCountState = true;
    }
    else if (dryRun_LastDistance > (Distance + 2))
    {
        debugln("all ok");
        dryRun_LastDistance = Distance;
        EEPROM.write(dryRun_LastDistance_mem, dryRun_LastDistance);
    }
}
#endif
