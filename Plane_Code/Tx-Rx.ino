
void rxSetup() {
  pinMode(A0, INPUT);
}

uint8_t Flight_mode() {
  float r1 = pulseIn(A0, HIGH) / 1000.0;
  if(r1 >= 1.8) return 2;
  else if(r1 <= 170 && r1>= 140) return 1;
  else return 0;
  
}

void autoPilot_on() {
  Attach_servos();
}

void auto_off() {
  Detach_servos();
}