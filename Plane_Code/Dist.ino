#include <NewPing.h>

#define PIN_PING 4        // Пин с Arduino соединен с пинами trigger и echo на датчике расстояния
#define PIN_Trigg 4       // Пин с Arduino соединен с пинами trigger и echo на датчике расстояния
#define MAX_DISTANCE 500  // Максимальное расстояние, которое мы способны контролировать (400-500см).

NewPing sonar(PIN_Trigg, PIN_PING, MAX_DISTANCE);  // Регулировка пинов и максимального расстояния
float k = 0.06;                                    // коэффициент фильтрации, 0.0-1.0

float expRunningAverageDist(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * k;
  return filVal;
}

float getDist() {                                                    // Опрашивать не чаще чем 40 мс
  float L = expRunningAverageDist((float)sonar.ping() / 57.5);  // Пересчет параметра времени в величину расстояния и вывод результата (0 соответствует выходу за допустимый предел)
  return L;
}