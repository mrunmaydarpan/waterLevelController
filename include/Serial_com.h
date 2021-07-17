void parseCommand(String com)
{
    if (com.startsWith("$"))
    {
        String part1 = com.substring(0, com.indexOf(":"));
        String part2 = com.substring(com.indexOf(":") + 1);

        if (part1.equals(GET_MIN))
        {
            int i = part2.toInt();
            if (i != 0)
            {
#if sonar
                if (i > 21)
                {
                    EEPROM.write(minDistance_mem, i);
                    MinDistance = i;
                }
                else
                {
                    EEPROM.write(minDistance_mem, 22);
                    MinDistance = 22;
                }
#else
                EEPROM.write(minDistance_mem, i);
#endif
            }
            else
            {
                EEPROM.write(minDistance_mem, 22);
            }
            Serial.print("minDistance set:");
            Serial.println(MinDistance);
        }
        else if (part1.equals(GET_MAX)) // $maxDistance 220
        {
            int i = part2.toInt();
            EEPROM.write(maxDistance_mem, i);
            MaxDistance = i;
            Serial.print("maxDistance set:");
            Serial.println(i);
        }
        else if (part1.equals(GET_THRESHOLD))
        {
            int i = part2.toInt();
            EEPROM.write(MotorStartThreshold_mem, i);
            MotorStartThreshold = i;
            Serial.print("start motor at: ");
            Serial.println(MotorStartThreshold);
        }

        else if (part1.equals(GET_PUMP))
        {
            int i = part2.toInt();
            if (i == 1)
            {
                ManualOff = false;
                EEPROM.write(manualOff_mem, 0);
                PumpON_command();
                if (AutoMode == false && modeButton.isPressed())
                {
                    AutoMode = true;
                }
            }
            else
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
            Serial.print("motor: ");
            Serial.println(i ? "on" : "off");
        }
        else if (part1.equals("$wifi"))
        {
            int i = part2.toInt();
            if (i)
            {
                lcd.setCursor(13, 1);
                lcd.write(3);
                Serial.println("WiFi Connected");
            }
            else
            {
                lcd.setCursor(13, 1);
                lcd.print(" ");
                Serial.println("WiFi Disconnected");
            }
        }
        else if (part1.equals(GET_SET))
        {
            Serial.println("get Code");
            Setting.println(GET_MIN + String(':') + String(MinDistance));
            Setting.println(GET_MAX + String(':') + String(MaxDistance));
            Setting.println(GET_THRESHOLD + String(':') + String(MotorStartThreshold));
        }
    }
}

// beta version, uncomment in void loop()
void setting()
{
    while (Setting.available())
    {
        char data = Setting.read();
        if (data == '\n')
        {
            parseCommand(Command);
            Command = "";
        }
        else
        {
            Command += data;
        }
    }
}
