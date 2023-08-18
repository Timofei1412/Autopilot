#define G433_SPEED 2000  // скорость 100-10000 бит/с

#include <Gyver433.h>
//Gyver433_RX<пин> tx;
Gyver433_TX<2, G433_XOR> tx;

struct data {
  uint16_t ax;
  uint16_t ay;
  uint16_t az;
  uint16_t speed;
};
data Data;


void setup() {
  Data.ax = 10;
  Data.ay = 2;
  Data.az = 0;
  Data.speed = 100;
}

void loop() {

  tx.sendData(Data);
  delay(100);
}
