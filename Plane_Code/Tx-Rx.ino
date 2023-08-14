
void rxSetup() {
  pinMode(A0, INPUT);
}

bool Flight_mode() {
  float r1 = pulseIn(A0, HIGH) / 1000.0;
  return r1 >= 1.8;
}

void autoPilot_on() {
  Attach_servos();
}

void auto_off() {
  Detach_servos();
}