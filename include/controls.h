void lcdDefault()
{
    lcd.setCursor(0, 0);
    lcd.print("PUMP:");
    lcd.setCursor(5, 0);
    lcd.print(MotorState ? "ON " : "OFF");
    lcd.setCursor(10, 0);
    lcd.print(AutoMode ? "  AUTO" : "MANUAL");
    lcd.setCursor(0, 1);
    lcd.print("Lv:");
}

void Debug()
{
    Serial.print("Lv:" + String(value));
    Serial.print("|");
    Serial.print(AutoMode ? "A" : "M");
    Serial.print("|");
    Serial.print("R:" + String(MotorState));
    Serial.print("|");
    Serial.print("MOff:" + String(ManualOff));
    Serial.print("|");
    Serial.print("Distance:" + String(Distance));
    Serial.print("|");
    Serial.print("MotoMode:" + String(STATOR_TYPE));
    Serial.print("|");
    Serial.print("DistX:" + String(DistanceX));
    Serial.println();
}

void buttonEvent()
{
    if (button.wasPressed())
    {
        if (MotorState == true)
        {
            if (value >= MotorStartThreshold)
            {
                ManualOff = false;
                EEPROM.write(manualOff_mem, 0);
            }
            else
            {
                ManualOff = true;
                AutoMode = false;
                EEPROM.write(manualOff_mem, 1);
            }
            PumpOFF_command();
        }
    }
    else if (button.pressedFor(LONG_PRESS))
    {
        ManualOff = false;
        DryRunState = false;
        errorCountState = false;
        EEPROM.write(manualOff_mem, 0);
        PumpON_command();
        if (AutoMode == false && modeButton.isPressed())
        {
            AutoMode = true;
        }
    }
    if (modeButton.wasPressed() && ManualOff == false)
    {
        AutoMode = true;
    }
    else if (modeButton.wasReleased())
    {
        AutoMode = false;
    }
}

void selectorMode()
{
    pinMode(selector_1, INPUT_PULLUP);
    pinMode(selector_2, INPUT_PULLUP);
    pinMode(selector_3, INPUT_PULLUP);

    if (digitalRead(selector_1) == LOW)
    {
        STATOR_TYPE = 1; // Normal Mode
    }
    else if (digitalRead(selector_2) == LOW)
    {
        STATOR_TYPE = 2; // Stator Mode
    }
    else if (digitalRead(selector_3) == LOW)
    {
        STATOR_TYPE = 3;
    }
}

void OneTimeRun()
{
    if (MotorState != LastMotorState)
    {
        Setting.println(SEND_PUMP + String(MotorState));
        if (MotorState == true)
        {
            motor_on();
#if DryRun
            dryRun_LastDistance = Distance;
            EEPROM.write(dryRun_LastDistance_mem, dryRun_LastDistance);
            dryRun_timer = t.every(DryRunTime, DRY_RUN_CHECK);
#endif
        }
        else
        {
            tone(buzz, 4500, 1000);
            digitalWrite(led, LOW);
            motor_off();
#if DryRun
            t.stop(dryRun_timer);
#endif
        }
        Serial.println("MotorState Changed");
    }
    LastMotorState = MotorState;
    EEPROM.write(LastMotorState_mem, LastMotorState);

    if (value != LastValue)
    {
    }
    LastValue = value;

    if (errorCountState != LasterrorCountState)
    {
        lcd.clear();
        Setting.println(SEND_ERROR + String(errorCountState));
        if (errorCountState == true)
        {
            PumpOFF_command();
            Serial.println("ERROR");
            ManualOff = true;
            AutoMode = false;
            EEPROM.write(manualOff_mem, 1);
            lcd.setCursor(3, 1);
            if (DryRunState)
            {
                lcd.print("DRY-RUN");
            }
            else
            {
                lcd.print("ERROR");
            }
            EEPROM.write(1, 0);
            ledBlink = t.oscillate(led, 500, HIGH);
        }
        else
        {
            t.stop(ledBlink);
            Serial.println("Error State Stop");
        }
    }
    LasterrorCountState = errorCountState;
}

void update_lcd()
{
    if (errorCountState == false)
    {
        lcd.setCursor(3, 1);
        lcd.print(value);
        lcd.print("%");
        lcd.print("   ");
    }
    lcd.setCursor(15, 1);
    if (blink_state == true)
    {
        blink_state = false;
        lcd.write(0);
    }
    else
    {
        lcd.write(1);
        blink_state = true;
    }
    Setting.println(SEND_VALUE + String(value));
    Setting.println(SEND_DISTANCE + String(Distance));
    Setting.println(SEND_MODE + String(AutoMode));
    Setting.println(SEND_ERROR + String(errorCountState));
}