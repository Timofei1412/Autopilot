#define Debug 0
#include "I2Cdev.h"
#include <GyverButton.h>


#define BTN_PIN 2  // кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
GButton butt1(BTN_PIN);

#define Radio433Pin 2

//Servo pins
#define PitchPin 10
#define RollPin 8
#define YawPin 9
#define AddPin 11


//Gyroscope is connected to pins  A4 and A5 relative to SDA and SCL on gyroscope
//Accelerometer is connected to pins  A4 and A5 relative to SDA and SCL on Accelerometer

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
float Ts = 0.0;   // Target speed


float globalSpeed = 0;

static uint32_t tmrM = 0;
static uint32_t tmrSpd = 0;
bool flightFlag = true;


//-Main Setup-----------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);  // Setup of main usb port for debug

  LedSetup();      //Setup of RGB led strip
  Gyrosetup();     // Setup of Gyroscope
  ServoSetup();    // Setup of Servo
  init_adxl345();  // Setup of accel
  rxSetup();

  butt1.setType(HIGH_PULL);  // Set the button type

  // Get angle data and set the "0" z angle to current
  getInfo(&rGx, &rGy, &rGz);
  rTz = rGz;

  delay(1000);
}
//-Logic Func----------------------------------------------------------------------------------------------------------------------------------------------------------------

//Plane is controled manualy, Arduino is counting speed, getting signals from ground and conrols Aeronautical lights
void flightData() {
  doLIght();                                                                                        // Aeronautical lights and landing lights are written here
  getAccel(&aGx, &aGy, &aGz);                                                                       // Get our acceleration
  globalSpeed += (((float)((int)(aGy * 100)) / 100) * 9.8 * ((millis() - tmrSpd) / 1000.0) * 3.6);  // Calculate our speed
  getSig();                                                                                         // Get signal from ground
  tmrSpd = millis();
}

//Plane is flying automatic, trying to fly staight (x = 0, y = 0, z = startZ)
void flyStraight() {
  doLIght();  // Aeronautical lights and landing lights are written here

  getInfo(&rGx, &rGy, &rGz);                                                                                                                                           // Get our angles
  angleWrite(constrain(computePid(rGy - 45, 0, 2), 10, 170), constrain(180 - computePid(rGx - 45, 0, 2), 10, 170), constrain(computePid(rGz - 45, rTz, 2), 10, 170));  // Calculate servo output

  getAccel(&aGx, &aGy, &aGz);  // Get our acceleration
  globalSpeed += (((float)((int)(aGy * 100)) / 100) * 9.8 * ((millis() - tmrSpd) / 1000.0) * 3.6);


  Gh = cos(radians(rGx)) * cos(radians(rGy)) * getDist();  // Get our height from sonic(from 1cm to 5m)
  debugPrint("Current speed is:", globalSpeed, "\t Current aGy is:", aGy, "\t aGy error is:", aGyError);

  getSig();  // Get signal from ground
  tmrSpd = millis();
}


//Plane is flying automatic, trying to mantain angles, given from ground
void flyWithTask() {
  doLIght();  // Aeronautical lights and landing lights are written here

  // Get our angles
  getInfo(&rGx, &rGy, &rGz);
  // Calculate servo output
  angleWrite(constrain(computePid(rGy - 45, rTy, 2), 10, 170), constrain(180 - computePid(rGx - 45, rTx, 2), 10, 170), constrain(computePid(rGz - 45, rTz, 2), 10, 170));

  Gh = cos(radians(rGx)) * cos(radians(rGy)) * getDist();  // Get our height from sonic
  getAccel(&aGx, &aGy, &aGz);                              // Get our acceleration
  globalSpeed += (((float)((int)(aGy * 100)) / 100) * 9.8 * ((millis() - tmrSpd) / 1000.0) * 3.6);

  debugPrint("Current speed is:", globalSpeed, "\t Current aGy is:", aGy, "\t aGy error is:", aGyError);
  getSig();
  tmrSpd = millis();
}

//-Main code-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void loop() {
  servoTick();   // обязательная функция отработки. Должна постоянно опрашиваться
  butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться

  //if button contriller set mode to autopilot
  if (Flight_mode()) {
    auto_on();
    if (flag) {
      // Get angle data and set the "0" z angle to current
      getInfo(&rGx, &rGy, &rGz);
      rTz = rGz;
      flag = false;
    }
    flyStraight();
  } else {
    auto_off();
    flag = true;
    flightData();
  }


  if (butt1.isClick()) {  // if button is clicked get acceleration error
    getAccel(&aGx, &aGy, &aGz);
    globalSpeed = 0.0;
    aGyError += aGy;
  }








  if (millis() - tmrM >= 40) {  // таймер на 40 мс (на всякий случай)
    if (Debug) {

    } else {
    }
    fly();
    tmrM = millis();  // сброс таймера
  }
}
