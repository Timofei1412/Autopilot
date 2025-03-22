#include <IBusBM.h>

IBusBM IBus; // IBus object

void rxSetup(){
  IBus.begin(Serial);
}
int val1, val2, val3, val4, val6;

void manualFlight(){
  val1 = IBus.readChannel(0); // get latest value for servo channel 1
  val2 = IBus.readChannel(1); // get latest value for servo channel 1
  val3 = IBus.readChannel(2); // get latest value for servo channel 1
  val4 = IBus.readChannel(3); // get latest value for servo channel 1
  angleWriteMicroseconds(val2, val1, val4, val3);
}

uint8_t Flight_mode() {
  val6 = IBus.readChannel(5); // get latest value for servo channel 1
  if(val6 >= 1300) return 1;
  else return 0; 
}
uint8_t GetEngine() {
  val3 = IBus.readChannel(2); // get latest value for servo channel 1
  return val3;
}
