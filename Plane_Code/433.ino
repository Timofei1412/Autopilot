#include <Gyver433.h>
Gyver433_RX<Radio433Pin, 24> rx;  // указали пин и размер буфера

void getSig() {
  if (rx.tick() == 24) {
    rx.readData(Income);
    rTx = Income.roll;
    rTy = Income.pitch;
    rTz = Income.yaw;

    kPX = (float)Income.Pr / 1000;
    kIX = (float)Income.Ir / 1000;
    kDX = (float)Income.Dr / 1000;

    kPY = (float)Income.Pp / 1000;
    kIY = (float)Income.Ip / 1000;
    kDY = (float)Income.Dp / 1000;

    kPZ = (float)Income.Py / 1000;
    kIZ = (float)Income.Iy / 1000;
    kDZ = (float)Income.Dy / 1000;
    Serial.print(rTx);
    Serial.print("-");
    Serial.print(rTy);
    Serial.print("-");
    Serial.print(rTz);
    Serial.print("-");

    Serial.print(kPX);
    Serial.print("-");
    Serial.print(kPY);
    Serial.print("-");
    Serial.print(kPZ);
    Serial.print("-");

    Serial.print(kIX);
    Serial.print("-");
    Serial.print(kIY);
    Serial.print("-");
    Serial.print(kIZ);
    Serial.print("-");

    Serial.print(kDX);
    Serial.print("-");
    Serial.print(kDY);
    Serial.print("-");
    Serial.print(kDZ);
    Serial.print("-");
  }
}
