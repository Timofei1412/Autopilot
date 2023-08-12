// Registers for ADXL345
#define ADXL345_ADDRESS (0xA6 >> 1)  // address for device
#define ADXL345_REGISTER_XLSB (0x32)

#define res 256
float X_out = 0;
float Y_out = 0;
float Z_out = 0;

void i2c_write(int address, byte reg, byte data) {
  Wire.beginTransmission(address);  // Connect to device
  Wire.write(reg);                  // Send data
  Wire.write(data);                 //low byte
  Wire.endTransmission();
}




void init_adxl345() {
  byte data = 0;

  i2c_write(ADXL345_ADDRESS, 0x31, 0x08);  // 13-bit mode +_ 4g
  i2c_write(ADXL345_ADDRESS, 0x2D, 0x08);  // Power register
  i2c_write(ADXL345_ADDRESS, 0x1E, 0x00);  // x
  i2c_write(ADXL345_ADDRESS, 0x1F, 0x00);  // Y
  i2c_write(ADXL345_ADDRESS, 0x20, 0x05);  // Z

  //X-axis
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x1E);  // X-axis offset register
  Wire.write(-round(-4 / 4));
  Wire.endTransmission();
  delay(10);
  //Y-axis
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x1F);  // Y-axis offset register
  Wire.write(-round(-5 / 4));
  Wire.endTransmission();
  delay(10);
  //Z-axis
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x20);  // Z-axis offset register
  Wire.write(-round(14 / 4));
  Wire.endTransmission();
  delay(10);


  for (int i = 0; i < 10; i++) {
    Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(0x32);  // Start with register 0x32 (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345_ADDRESS, 6, true);  // Read 6 registers total, each axis value is stored in 2 registers
    X_out = (Wire.read() | Wire.read() << 8);    // X-axis value
    Y_out = (Wire.read() | Wire.read() << 8);    // Y-axis value
    Z_out = (Wire.read() | Wire.read() << 8);    // Z-axis value

    Serial.print("X: ");
    Serial.print(X_out);
    Serial.print('\t');
    Serial.print("Y: ");
    Serial.print(Y_out);
    Serial.print('\t');
    Serial.print("Z: ");
    Serial.print(Z_out);
    Serial.println('\t');
  }
  delay(500);
  Serial.println("--------------------------------------------------------------------------");
}

float kA = 0.2;  // коэффициент фильтрации, 0.0-1.0

float expRunningAverageAccel(float *ax, float *ay, float *az) {
  static float pax = 0, pay = 0, paz = 0;
  pax += (*ax - pax) * kA;
  pay += (*ay - pay) * kA;
  paz += (*az - paz) * kA;

  *ax = pax;
  *ay = pay;
  *az = paz;
}


void getAccel(float *ax, float *ay, float *az) {
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x32);  // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345_ADDRESS, 6, true);  // Read 6 registers total, each axis value is stored in 2 registers
  X_out = (Wire.read() | Wire.read() << 8);    // X-axis value
  X_out = X_out / res;                         //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = (Wire.read() | Wire.read() << 8);    // Y-axis value
  Y_out = Y_out / res;
  Z_out = (Wire.read() | Wire.read() << 8);  // Z-axis value
  Z_out = Z_out / res;
  expRunningAverageAccel(&X_out, &Y_out, &Z_out);
  *ax = X_out;
  *ay = Y_out - aGyError;
  *az = Z_out;
}