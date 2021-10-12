void StartUp()
{
    const char *compile_date = __DATE__;
    const char *compile_time = __TIME__;
    debugln(F("Ready......."));
    debugln("SW: " + String(version));
    debugln("DT: " + String(compile_date) + " | " + String(compile_time));
    debugln("MaxDistance: " + String(MaxDistance));
    debugln("MinDistance: " + String(MinDistance));
    debugln("start at: " + String(MotorStartThreshold));
    debugln("ManualOff: " + String(EEPROM.read(manualOff_mem)));
    debugln("MotorState: " + String(EEPROM.read(motorState_mem)));
    debugln("Mode: " + String(AutoMode));
    debug(F("Starting."));
    lcd.clear();
    lcd.setCursor(11, 0);
    lcd.print("v" + String(version));
    lcd.setCursor(0, 1);
    lcd.print(compile_date);
    pinMode(buzz, OUTPUT);
    for (int l = 0; l < int(sizeof(brand) - 1); l++)
    {
        lcd.setCursor(l, 0);
        lcd.print(brand[l]);
        // tone(buzz, 4500, 150);
        digitalWrite(led, !digitalRead(led));
        debug_led(true);
        debug(F("."));
        delay(300);
    }
    debugln();
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
    // while (digitalRead(selector_1) == HIGH &&
    //        digitalRead(selector_2) == HIGH &&
    //        digitalRead(selector_3) == HIGH)
    // {
    //     lcd.setCursor(0, 0);
    //     lcd.print("PUMP TYPE ERROR ");
    //     lcd.setCursor(0, 1);
    //     lcd.print("set pump type   ");
    // }
    delay(2000);
    lcd.clear();
    digitalWrite(led, LOW);
}

void WireTestMode()
{
#if TestMode
    pinMode(selector_1, INPUT_PULLUP);
    lcd.clear();
    while (digitalRead(selector_1) == LOW)
    {
        lcd.print("WIRE TEST MODE");
        pinMode(EchoPin, OUTPUT);
        pinMode(TriggerPin, OUTPUT);
        digitalWrite(EchoPin, HIGH);
        digitalWrite(TriggerPin, HIGH);
    }
#endif
}