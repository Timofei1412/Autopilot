// демо-пример отправки
// SYN115, маленький чип: 1.8-3.6V
// FS1000A: 3-12V
// WL102-341: 2.0-3.6V

// дефайны перед подключением библиотеки
//#define G433_FAST         // короткая синхронизация для зелёных модулей
//#define G433_MEDIUM       // средняя синхронизация для SYN480R при отправке ЧАЩЕ 400мс (активно по умолчанию)
//#define G433_SLOW         // длинная синхронизация для SYN480R при отправке РЕЖЕ 400мс
#define G433_SPEED 2000  // скорость 100-10000 бит/с, по умолч. 2000 бит/с

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

  // отправка 10 раз в сек
  delay(100);
}
