// This log Acc from MPU6050
// Data writes to SDcard
// pin number is GPIO

#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// SPI-SD-config
const int _MISO = 4;
const int _MOSI = 7;
const int _CS = 5;
const int _SCK = 6;
File myFile;
SPISettings spisttings(10000000, MSBFIRST, SPI_MODE3);

// I2C-MPU6050-config
const int _SDA = 0;
const int _SCL = 1;
const int i2cClock = 400000;
const int MPU6050_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float AccX, AccY, AccZ, GyrX, GyrY, GyrZ;

void setup() {
  // start serial
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  // start i2c-MPU6050
  Wire.setSDA(_SDA);
  Wire.setSCL(_SCL);
  Wire.setClock(i2cClock);
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // start SPI-SD
  Serial.println("Initializing SD card...");
  SPI.setCS(_CS);
  SPI.setRX(_MISO);
  SPI.setSCK(_SCK);
  SPI.setTX(_MOSI);
  SPI.begin();

  while (!SD.begin(_CS)) {
    Serial.println("initialization failed!");
    delay(1000);
  }
  Serial.println("initialization done.");
}

void loop() {
  getRawData();
  getCalcData();
  SDwrite();
  SDread();
}

void getRawData() {
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read();      // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();      // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();      // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();      // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read();      // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();      // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();      // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void getCalcData() {
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
  Serial.print(Tmp / 340.00 + 36.53);
  Serial.print(" degC| GyrX = ");
  Serial.print(GyrX);
  Serial.print(" deg/s | GyrY = ");
  Serial.print(GyrY);
  Serial.print(" deg/s | GyrZ = ");
  Serial.print(GyrZ);
  Serial.println(" deg/s ");
}

void SDwrite() {
  myFile = SD.open("MPU6050.txt", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to MPU6050.txt...");
    myFile.print(AccX);
    myFile.print(",");
    myFile.print(AccY);
    myFile.print(",");
    myFile.print(AccZ);
    myFile.print(",");
    myFile.print(Tmp / 340.00 + 36.53);
    myFile.print(",");
    myFile.print(GyrX);
    myFile.print(",");
    myFile.print(GyrY);
    myFile.print(",");
    myFile.print(GyrZ);
    myFile.print(",");
    myFile.print("\n");
    Serial.println("Done!");
    myFile.close();
  } else {
    Serial.println("error");
  }
}

void SDread() {
  myFile = SD.open("MPU6050.txt");
  if (myFile) {
    Serial.println("MPU6050.txt:");

    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    Serial.println("error");
  }
}
