#define Debug 1
#define Radio433Pin 2

//Servo pins
#define PitchPin 10
#define RollPin 5
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
float kPX = 2.5;
float kIX = 0.005;
float kDX = 0;

//-Coef for the Y angle------------------------------------------
float kPY = 2;
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
class PID {
public:
	float p = 0;
	float i = 0;
	float d = 0;
	float limit = 0;

	float derivative = 0;
	float integral = 0;

	PID(float p, float i, float d, float windup = 0) : p(p), i(i), d(d), limit(windup)  {};

	float update(float error, float dt) {
		integral += error * dt;

		if (isfinite(prevError) && dt > 0) {
			derivative = (error - prevError) / dt;
		}

		prevError = error;

		return p * error + constrain(i * integral, -limit, limit) + d * derivative; // PID
	}

	void reset() {
		prevError = NAN;
		integral = 0;
		derivative = 0;
	}

private:
	float prevError = NAN;
};


PID Pitch(1, 0, 0, 10);
PID Roll(1, 0, 0, 10);
PID Yaw(1, 0, 0, 10);
PID Engine(1, 0, 0, 10);

void setup() {
  Serial.begin(115200);  // Setup of main usb port for debug
  delay(4000);
  LedSetup();   //Setup of RGB led strip
  Gyrosetup();  // Setup of Gyroscope
  ServoSetup();    // Setup of Servo
  rxSetup();
  delay(100);
}
long long flightTmr = 0;

void levelOff(){
  getInfo(&rGx, &rGy, &rGz);
  debugPrint("x:", rGx, " y:", rGy, "z:", rGz);
  float x = Pitch.update(rGx, (millis() - flightTmr)/1000);
  float y = Roll.update(rGy, (millis() - flightTmr)/1000);
  float z = Yaw.update(rGz, (millis() - flightTmr)/1000);

  angleWrite(90 - y, 90 + x, 90 - z);
  flightTmr = millis();
}

//-Main code-----------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8_t currentMode = 0;
long long modeTMR  = 0;
void loop() {  
  currentMode = Flight_mode();
  // levelOff();
  switch (currentMode){
    case 0:
      manualFlight();
    break;
    case 1:
      levelOff();
      break;
  };
}