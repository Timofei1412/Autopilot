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

void Attach_servos() {
  //if servo is not controled by the Arduino Begin controlling
  if (~(ServoPitch.attached())) ServoPitch.attach(PitchPin);
  if (~(ServoRoll.attached())) ServoRoll.attach(RollPin);
  if (~(ServoYaw.attached())) ServoYaw.attach(YawPin);
  if (~(ServoEng.attached())) ServoEng.attach(EngPin);
}


void Detach_servos() {
  //If servo is controlled by Arduino Stop conrolling
  if (ServoPitch.attached()) {
    ServoPitch.write(90);
    delay(100);
    ServoPitch.detach();
    pinMode(PitchPin, LOW);
  }

  if (ServoRoll.attached()) {
    ServoRoll.write(90);
    delay(100);
    ServoRoll.detach();
    pinMode(RollPin, LOW);
  }

  if (ServoYaw.attached()) {
    ServoYaw.write(90);
    delay(100);
    ServoYaw.detach();
    pinMode(YawPin, LOW);
  }
  if (ServoEng.attached()) {
    ServoEng.write(90);
    delay(100);
    ServoEng.detach();
    pinMode(EngPin, LOW);
  }
}