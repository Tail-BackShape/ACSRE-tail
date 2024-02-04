#include <Wire.h>
#define Addr_Accl 0x19

float xAccl = 0.00;
float yAccl = 0.00;
float zAccl = 0.00;

void setup() {

  Wire.begin();
  Serial.begin(9600);
  BMX055_Init();
  delay(300);
}

void loop() {

  BMX055_Accl();
  Serial.print("Accl= ");
  Serial.print(xAccl);
  Serial.print(",");
  Serial.print(yAccl);
  Serial.print(",");
  Serial.print(zAccl);
  Serial.println("");

  check_zAccl(zAccl);

  delay(100);
}


void BMX055_Init() {

  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x0F);  // Select PMU_Range register
  Wire.write(0x03);  // Range = +/- 2g
  Wire.endTransmission();
  delay(100);

  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x10);  // Select PMU_BW register
  Wire.write(0x08);  // Bandwidth = 7.81 Hz
  Wire.endTransmission();
  delay(100);

  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x11);  // Select PMU_LPW register
  Wire.write(0x00);  // Normal mode, Sleep duration = 0.5ms
  Wire.endTransmission();
  delay(100);
}
//=====================================================================================//
void BMX055_Accl() {
  unsigned int data[6];
  
  for (int i = 0; i < 6; i++) {
    Wire.beginTransmission(Addr_Accl);
    Wire.write((2 + i));
    Wire.endTransmission();
    Wire.requestFrom(Addr_Accl, 1);
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }

  xAccl = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
  if (xAccl > 2047) xAccl -= 4096;
  yAccl = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
  if (yAccl > 2047) yAccl -= 4096;
  zAccl = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
  if (zAccl > 2047) zAccl -= 4096;
  xAccl = xAccl * 0.00098;  // range = +/-2g
  yAccl = yAccl * 0.00098;  // range = +/-2g
  zAccl = zAccl * 0.00098;  // range = +/-2g
}

void check_zAccl(float zAccl){
  if (zAccl < 0){
    pinMode(ServoPin, HIGH);
  } 
}