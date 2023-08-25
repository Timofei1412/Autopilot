#define Debug 1


#define Radio433Pin 2

//Servo pins
#define PitchPin 10
#define RollPin 8
#define YawPin 9
#define EngPin 11


//Gyroscope is connected to pins  A4 and A5 relative to SDA and SCL on gyroscope


//-Vals-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
float rGx = 0.0;  // Global X Angle
float rGy = 0.0;  // Global Y Angle
float rGz = 0.0;  // Global Z Angle
float Gh = 0.0;   // Global height

float aGx = 0.0;  // Global X acceleration
float aGy = 0.0;  // Global Y acceleration
float aGz = 0.0;  // Global Z acceleration

float aGyError = 0.0;

float rTx = 0.0;  // Target x angle
float rTy = 0.0;  // Target y angle
float rTz = 0.0;  // Target z angle

//-Coef for the X angle------------------------------------------
float kPX = 1;
float kIX = 0;
float kDX = 0;

//-Coef for the Y angle------------------------------------------
float kPY = 1;
float kIY = 0;
float kDY = 0;

//-Coef for the Z angle------------------------------------------
float kPZ = 1;
float kIZ = 0;
float kDZ = 0;



float globalSpeed = 0;

static uint32_t tmrM = 0;
static uint32_t tmrSpd = 0;
bool flightFlag = true;


//-Main Setup-----------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "I2Cdev.h"
#include "Led.h"


void setup() {
  Serial.begin(115200);  // Setup of main usb port for debug

  LedSetup();   //Setup of RGB led strip
  Gyrosetup();  // Setup of Gyroscope
  //ServoSetup();    // Setup of Servonjjlk
  rxSetup();

  delay(1000);
}


//-Main code-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  servoTick();  // обязательная функция отработки. Должна постоянно опрашиваться

  if (Flight_mode() == 1) {  //if button controller set mode to autopilot straight
    autoPilot_on();
    if (flightFlag) {  // Do it one time
      // Get angle data and set the "0" z angle to current
      getInfo(&rGx, &rGy, &rGz);
      rTz = rGz;
      flightFlag = false;
    }
    flyStraight();
  } else if (Flight_mode() == 2) {  //if button controller set mode to autopilot task
    autoPilot_on();
    if (flightFlag) {  // Do it one time
      // Get angle data and set the "0" z angle to current
      getInfo(&rGx, &rGy, &rGz);
      rTz = rGz;
      flightFlag = false;
    }

    flyWithTask();

  } else {  //if button controller set mode to manual
    auto_off();
    flightFlag = true;
    flightData();
  }
  getSig();  // Get signal from ground
}
