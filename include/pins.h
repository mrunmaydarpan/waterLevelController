#define Mode 3
#define PB 0
#define led 2
#define buzz 15
#define Relay_ON 12
#define Relay_ON_2 13
#define Relay_OFF 14

#if sonar
#define EchoPin 10
#define TriggerPin 9 // need to swap
#else
#define sensorRX 10
#define sensorTX 9
#endif