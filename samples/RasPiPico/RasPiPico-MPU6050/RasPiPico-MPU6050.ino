#include <Wire.h>
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float AccX, AccY, AccZ, GyrX, GyrY, GyrZ;
void setup()
{
  Wire.setSDA(0); // I2C0 SDA GP4
  Wire.setSCL(1); // I2C0 SCL GP5
  Wire.setClock(400000);
  Wire.begin();
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
}
void loop()
{
  displayRawData();
  displaySiData();
  delay(100);
}

void displayRawData()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = ");
  Serial.print(AcX);
  Serial.print(" | AcY = ");
  Serial.print(AcY);
  Serial.print(" | AcZ = ");
  Serial.print(AcZ);
  Serial.print(" | Tmp = ");
  Serial.print(Tmp / 340.00 + 36.53); // equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = ");
  Serial.print(GyX);
  Serial.print(" | GyY = ");
  Serial.print(GyY);
  Serial.print(" | GyZ = ");
  Serial.println(GyZ);
}

void displaySiData()
{
  AccX = AcX / 16384.0;
  AccY = AcY / 16384.0;
  AccZ = (AcZ / 16384.0) - 0.18;

  GyrX = (GyX / 131.0) - 3.2;
  GyrY = (GyY / 131.0) - 2.0;
  GyrZ = (GyZ / 131.0) - 0.2;

  Serial.print("AccX = ");
  Serial.print(AccX);
  Serial.print(" g | AccY = ");
  Serial.print(AccY);
  Serial.print(" g | AccZ = ");
  Serial.print(AccZ);
  Serial.print(" g | Tmp = ");
  Serial.print(Tmp / 340.00 + 36.53); // equation for temperature in degrees C from datasheet
  Serial.print(" degC| GyrX = ");
  Serial.print(GyrX);
  Serial.print(" deg/s | GyrY = ");
  Serial.print(GyrY);
  Serial.print(" deg/s | GyrZ = ");
  Serial.print(GyrZ);
  Serial.println(" deg/s ");
}
