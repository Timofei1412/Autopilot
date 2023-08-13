#include "SoftServo.h"

SoftServo ServoPitch;  // Y
SoftServo ServoRoll;   // x
SoftServo ServoYaw;    // z
SoftServo ServoEng;    // Additional servo (For any other purpose)


void ServoSetup() {
  // Attach pin to servo
  ServoPitch.attach(PitchPin);
  ServoRoll.attach(RollPin);
  ServoYaw.attach(YawPin);
  ServoEng.attach(EngPin);
  // Make async mode to get rid of delays
  ServoPitch.asyncMode();
  ServoRoll.asyncMode();
  ServoYaw.asyncMode();
  ServoEng.asyncMode();
}

void servoTick() {
  ServoPitch.tick();
  ServoRoll.tick();
  ServoYaw.tick();
}

void angleWrite(int x, int y, int z) {
  ServoPitch.write(x);
  ServoRoll.write(y);
  ServoYaw.write(z);
}

// 0 - Pitch, 1 - Roll, 2 - Yaw, 3 - Additional Servo
void indServoAngle(int angle, uint8_t servoType) {
  switch (servoType) {
    case 0:
      {
        ServoPitch.write(angle);
        break;
      }
    case 1:
      {
        ServoRoll.write(angle);
        break;
      }
    case 2:
      {
        ServoYaw.write(angle);
        break;
      }
    case 3:
      {
        ServoEng.write(angle);
        break;
      }
  }
}