#include <setting.h>
#include <includes.h>

#define motorState_mem 1
#define maxDistance_mem 2
#define minDistance_mem 3
#define MotorStartThreshold_mem 4
#define manualOff_mem 5
#define LastMotorState_mem 6
#define dryRun_LastDistance_mem 7
#define StatorType_mem 8

int MinDistance;
int MotorStartThreshold;
int MaxDistance, value, LastValue;
uint8_t STATOR_TYPE;
uint8_t errorCount;
// uint8_t okCount;
uint8_t ledBlink;
uint8_t LCD_t;
uint8_t RELAY_OFF;
int Distance, DistanceX;
#if DryRun
int dryRun_timer;
#endif
uint8_t dryRun_Distance(0), dryRun_LastDistance(0);

const unsigned long LONG_PRESS(2000);

bool MotorState, LastMotorState;
bool AutoMode = false;
bool ManualOff = false;
bool blink_state = false;
bool errorCountState, LasterrorCountState;
bool WiFiState;
bool DryRunState;

String Command;
unsigned char data[4] = {};

byte BlinkUp[] = {B11111, B11111, B11111, B11111,
                  B00000, B00000, B00000, B00000};

byte BlinkDown[] = {B00000, B00000, B00000, B00000,
                    B11111, B11111, B11111, B11111};

byte ManualOff_char[] = {
    0x02,
    0x02,
    0x06,
    0x1F,
    0x1F,
    0x1E,
    0x0E,
    0x0E};
byte network_icon[] = {
    0x00,
    0x0A,
    0x0B,
    0x0A,
    0x0A,
    0x1A,
    0x0A,
    0x00};

#include <headers.h>

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, BlinkUp);
  lcd.createChar(1, BlinkDown);
  lcd.createChar(2, ManualOff_char);
  lcd.createChar(3, network_icon);

#if sonar
#else
  sensorSerial.begin(9600);
#endif
  ReadMem();
  button.begin();
  modeButton.begin();
  pinMode(Relay_ON, OUTPUT);
  pinMode(Relay_OFF, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);
#if debug_led_state
  pinMode(debug_led_pin, OUTPUT);
#endif
  if (ManualOff == false && digitalRead(Mode) == LOW)
  {
    AutoMode = true;
  }
  else
  {
    AutoMode = false;
  }

  StartUp();
  if (MotorState == true && ManualOff == false && AutoMode == true)
  {
    debugln("turning motor on");
    LastMotorState = false;
    PumpON_command();
  }
  else
  {
    PumpOFF_command();
  }
  t.every(100, readSensor);
  t.every(500, update_lcd);
#if debugData
  t.every(1000, Debug);
#endif

  mySensor.begin(SMOOTHED_AVERAGE, 50);
  // mySensor.clear();
#if LCD_BL_OFF
  LCD_t = t.after(5000, lcd_off);
#endif
}

void loop()
{
  t.update();
  button.read();
  modeButton.read();
  lcdDefault();
  buttonEvent();
  OneTimeRun();
  if (ManualOff == true)
  {
    lcd.setCursor(14, 1);
    lcd.write(2);
  }
  else
  {
    lcd.setCursor(14, 1);
    lcd.print(" ");
  }
}