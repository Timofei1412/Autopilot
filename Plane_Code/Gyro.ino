#include "MPU6050_6Axis_MotionApps20.h"

#define kX 0.1
#define kY 0.1
#define kZ 0.1

MPU6050 mpu;
uint8_t fifoBuffer[45];  // буфер

float filX = 0;
float filY = 0;
float filZ = 0;

void Gyrosetup() {
  Wire.begin();
  //Wire.setClock(1000000UL);   // разгоняем шину на максимум
  // инициализация DMP
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
  mpu.CalibrateAccel(3);
  mpu.CalibrateGyro(3);
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

    filX += (degrees(ypr[2])- filX) * kX;
    filY += (degrees(ypr[1])- filY) * kY;
    filZ += (degrees(ypr[0])- filZ) * kZ;

    *rx = filX;
    *ry = filY;
    *rz = filZ;
  }
}