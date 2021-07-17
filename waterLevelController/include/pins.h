#define Mode A2
#define PB A3
#define led A1
#define buzz A0
#define Relay_ON 12
#define Relay_OFF 11
#define debug_led 13
#define selector_1 5
#define selector_2 6
#define selector_3 7
#define EspRx 2
#define EspTx 3

#if sonar
#define EchoPin 10
#define TriggerPin 9  //need to swap
#else
#define sensorRX 10
#define sensorTX 9
#endif
