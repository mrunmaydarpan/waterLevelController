#define version "5.9f"
#define hardware "3.1"
const char brand[] = "MDtronix";

/*------------function setting-----------------*/
#define sonar true
#define DryRun true
#define level_5 false
/*---------------------------------------------*/

#define debugData true  //default: true
#define wifi_test false //default: false

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