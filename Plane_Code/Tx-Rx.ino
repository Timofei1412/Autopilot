
/*
 Поменять названия серв.
*/
void rxSetup() {
  pinMode(A0, INPUT);
}

bool Flight_mode() {
  float r1 = pulseIn(A0, HIGH) / 1000.0;
  return r1 >= 1.8;
}

void auto_on() {
  if (~elevator.attached()) {
    elevator.attach(3);
  }
  if (~eleron.attached()) {
    eleron.attach(9);
  }
}

void auto_off() {
  if (elevator.attached()) {
    elevator.write(90);
    delay(100);
    elevator.detach();
    pinMode(3, LOW);
  }

  if (eleron.attached()) {
    eleron.write(90);
    delay(100);
    eleron.detach();
    pinMode(9, LOW);
  }
}