#include <setting.h>

int MinDistance;
int MotorStartThreshold;
int MaxDistance, value, LastValue;
uint8_t maxDistance_mem(2), minDistance_mem(3);
uint8_t manualOff_mem(5);
uint8_t motorState_mem(1), LastMotorState_mem(6);
uint8_t MotorStartThreshold_mem(4);
uint8_t dryRun_LastDistance_mem(7);
uint8_t STATOR_TYPE;
uint8_t errorCount;
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
    0x01,
    0x1F,
    0x11,
    0x11,
    0x1F,
    0x1F,
    0x1F,
    0x1F};

#include <headers.h>

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
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
  pinMode(debug_led, OUTPUT);

  if (ManualOff == false && digitalRead(Mode) == LOW)
  {
    AutoMode = true;
  }
  else
  {
    AutoMode = false;
  }
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, BlinkUp);
  lcd.createChar(1, BlinkDown);
  lcd.createChar(2, ManualOff_char);
  lcd.createChar(3, network_icon);
  selectorMode();
  StartUp();

  if (MotorState == true && ManualOff == false && AutoMode == true)
  {
    Serial.println("turning motor on");
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
  Setting.println(GET_MIN + String(':') + String(MinDistance));
  Setting.println(GET_MAX + String(':') + String(MaxDistance));
  Setting.println(GET_THRESHOLD + String(':') + String(MotorStartThreshold));
  Setting.println(SEND_PUMP + String(MotorState));
  mySensor.begin(SMOOTHED_AVERAGE, 50);
  mySensor.clear();
}

void loop()
{
  t.update();
  button.read();
  modeButton.read();
  lcdDefault();
  buttonEvent();
  OneTimeRun();
  setting();
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