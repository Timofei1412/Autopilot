#include <Gyver433.h>
Gyver433_RX<Radio433Pin, 24> rx;  // указали пин и размер буфера

struct data {
  int roll;
  int pitch;
  int yaw;

  int Pr;
  int Ir;
  int Dr;

  int Pp;
  int Ip;
  int Dp;

  int Py;
  int Iy;
  int Dy;
};
data Income;

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
  }
}
