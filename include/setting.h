#define version "6.1a"
#define hardware "4.0"
const char brand[] = "MDtronix";

/*------------function setting-----------------*/
#define sonar true
#define DryRun false
/*---------------------------------------------*/

#define debugData true  //default: true
#define wifi_test false //default: false
#define debug_led_state true

#define on_delay 300
#define off_delay 200

#if wifi_test
#define Setting Serial
#else
#define Setting mySerial
#endif
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
SoftwareSerial mySerial(EspRx, EspTx);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Button button(PB);
Button modeButton(Mode);
Timer t;
Smoothed<int> mySensor;