#if DryRun
#define DryRunTime 120000
#endif

#if debugData
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

#if debug_led_state
#define debug_led(state) digitalWrite(debug_led_pin, state)
#else
#define debug_led(state)
#endif

#if Buzzer
#define Buzz(pin, STATE) digitalWrite(pin,STATE)
#else
#define Buzz(pin, STATE)
#endif

#include <JC_Button.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Timer.h>
#if sonar
#include <Ultrasonic.h>
#endif
#include <Smoothed.h>
#include <wifiCom.h>
#include <pins.h>

#if sonar
Ultrasonic Sonar(TriggerPin, EchoPin);
#else
SoftwareSerial sensorSerial(sensorRX, sensorTX);
#endif
LiquidCrystal_I2C lcd(0x27, 16, 2);
Button button(PB);
Button modeButton(Mode);
Timer t;
Smoothed<uint8_t> mySensor;