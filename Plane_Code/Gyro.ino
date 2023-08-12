#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;
uint8_t fifoBuffer[45];  // буфер

void Gyrosetup() {
  Wire.begin();
  //Wire.setClock(1000000UL);   // разгоняем шину на максимум
  // инициализация DMP
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  Serial.print("Wait!");
  mpu.CalibrateAccel(6);
  mpu.CalibrateGyro(6);
  Serial.println("GO");
}

// Прередавать &ax,&ay,&az
void getInfo(float *rx, float *ry, float *rz) {
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    // переменные для расчёта (ypr можно вынести в глобал)
    Quaternion q;
    VectorFloat gravity;
    float ypr[3];
    // расчёты
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    // Serial.print(degrees(ypr[2]));  // вокруг оси X
    // Serial.print('\t');
    // Serial.print(degrees(ypr[1]));  // вокруг оси Y
    // Serial.print('\t');
    // Serial.print(degrees(ypr[0]));  // вокруг оси Z
    // Serial.print('\t');
    *rx = degrees(ypr[2]);
    *ry = degrees(ypr[1]);
    *rz = degrees(ypr[0]);
  }
}