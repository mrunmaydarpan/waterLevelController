void StartUp()
{
    const char *compile_date = __DATE__;
    const char *compile_time = __TIME__;
    Serial.println(F("Ready......."));
    Serial.println("SW: " + String(version));
    Serial.println("DT: " + String(compile_date) + " | " + String(compile_time));
    Serial.println("MaxDistance: " + String(MaxDistance));
    Serial.println("MinDistance: " + String(MinDistance));
    Serial.println("start at: " + String(MotorStartThreshold));
    Serial.println("ManualOff: " + String(EEPROM.read(manualOff_mem)));
    Serial.println("MotorState: " + String(EEPROM.read(motorState_mem)));
    Serial.println("Mode: " + String(AutoMode));
    Serial.print(F("Starting."));
    lcd.clear();
    lcd.setCursor(11, 0);
    lcd.print("v" + String(version));
    lcd.setCursor(0, 1);
    lcd.print(compile_date);
    for (int l = 0; l < int(sizeof(brand) - 1); l++)
    {
        lcd.setCursor(l, 0);
        lcd.print(brand[l]);
        tone(buzz, 4500, 150);
        digitalWrite(led, !digitalRead(led));
        digitalWrite(debug_led, !digitalRead(debug_led));
        Serial.print(F("."));
        delay(300);
    }
    Serial.println();
    delay(500);
    char showVersion[14];
    char showData[16];
    sprintf(showVersion, "HW:%s", hardware);
    sprintf(showData, "L:%d H:%d P:%d", MaxDistance, MinDistance, MotorStartThreshold);
    lcd.clear();
    lcd.print(showVersion);
    lcd.setCursor(0, 1);
    lcd.print(showData);
    lcd.setCursor(14, 0);
#if sonar
    lcd.print("U");
#else
    lcd.print("S");
#endif
    lcd.setCursor(15, 0);
    lcd.print(STATOR_TYPE);
    while (digitalRead(selector_1) == HIGH &&
           digitalRead(selector_2) == HIGH &&
           digitalRead(selector_3) == HIGH)
    {
        lcd.setCursor(0, 0);
        lcd.print("PUMP TYPE ERROR ");
        lcd.setCursor(0, 1);
        lcd.print("set pump type   ");
    }
    delay(2000);
    lcd.clear();
    digitalWrite(led, LOW);
}