#define G433_SPEED 2000  // скорость 100-10000 бит/с, по умолч. 2000 бит/с

#include <Gyver433.h>
//Gyver433_RX<пин> tx;
Gyver433_TX<2> tx;

#define EB_CLICK 300  // таймаут накликивания, мс

#include <EncButton.h>
EncButton<EB_TICK, 4, 5, 6> enc;  // энкодер с кнопкой <A, B, KEY>



void setup() {
  Serial.begin(9600);
}
float val[12] = { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 };
int data[12];

int mode = 0;

bool flag = false;
unsigned long long tmr = 0;
void loop() {
  enc.tick();  // опрос происходит здесь
  if (millis() - tmr >= 1000) {
    data[0] = val[0];
    data[1] = val[1];
    data[2] = val[2];

    data[3] = val[3] * 1000;
    data[4] = val[4] * 1000;
    data[5] = val[5] * 1000;

    data[6] = val[6] * 1000;
    data[7] = val[7] * 1000;
    data[8] = val[8] * 1000;

    data[9] = val[9] * 1000;
    data[10] = val[10] * 1000;
    data[11] = val[11] * 1000;

    tx.sendData(data);
    Serial.println("===========-----------=====================");
    tmr = millis();
  }

  if (enc.click()) {
    flag = !flag;
  }
  if (enc.held() && flag == 0) {
    tx.sendData(val);
    Serial.println("===========-----------=====================");
  }

  if (!flag) {
    if (enc.right()) mode++;  // поворот направо
    if (enc.left()) mode--;   // поворот налево
    if (mode >= 11) mode = 11;
    if (mode <= 0) mode = 0;

  } else {
    if (mode == 0 || mode == 1 || mode == 2) {
      if (enc.right()) val[mode] += 1.0;    // поворот направо
      if (enc.left()) val[mode] -= 1.0;     // поворот налево
      if (enc.leftH()) val[mode] -= 10.0;   // нажатый поворот налево
      if (enc.rightH()) val[mode] += 10.0;  // нажатый поворот направо
    } else {
      if (enc.right()) val[mode] += 0.01;  // поворот направо
      if (enc.left()) val[mode] -= 0.01;   // поворот налево
      if (enc.leftH()) val[mode] -= 1;     // нажатый поворот налево
      if (enc.rightH()) val[mode] += 1.0;  // нажатый поворот направо
    }
    val[0] = constrain(val[0], -50, 50);
    val[1] = constrain(val[1], -30, 30);
    val[2] = constrain(val[1], 0, 360);
  }

  Serial.print(mode);
  Serial.print('\t');
  for (int i = 0; i < 11; i++) {
    Serial.print(val[i]);
    Serial.print("_");
  }
  Serial.print(val[11]);
  Serial.print('\t');
  Serial.println(flag);

  Serial.print("--------");
  for (int i = 0; i < mode; i++) {
    Serial.print("-----");
  }
  Serial.print("|^^|-");
  for (int i = mode + 1; i < 12; i++) {
    Serial.print("-----");
  }
  Serial.println();
  delay(200);
}

void yield() {
  enc.tick();  // опрос происходит здесь
  if (enc.click()) flag = !flag;
  if (!flag) {
    if (enc.right()) mode++;  // поворот направо
    if (enc.left()) mode--;   // поворот налево
    if (mode >= 11) mode = 11;
    if (mode <= 0) mode = 0;

  } else {
    if (mode == 0 || mode == 1 || mode == 2) {
      if (enc.right()) val[mode] += 1.0;    // поворот направо
      if (enc.left()) val[mode] -= 1.0;     // поворот налево
      if (enc.leftH()) val[mode] -= 10.0;   // нажатый поворот налево
      if (enc.rightH()) val[mode] += 10.0;  // нажатый поворот направо
    } else {
      if (enc.right()) val[mode] += 0.01;  // поворот направо
      if (enc.left()) val[mode] -= 0.01;   // поворот налево
      if (enc.leftH()) val[mode] -= 1;     // нажатый поворот налево
      if (enc.rightH()) val[mode] += 1.0;  // нажатый поворот направо
    }
    val[0] = constrain(val[0], -50, 50);
    val[1] = constrain(val[1], -30, 30);
  }
}
