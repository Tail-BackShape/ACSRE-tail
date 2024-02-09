#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

float PressureZero;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }

  //get P0
  delay(1000);
  PressureZero = bmp.readPressure();
}

void loop() {
  //get info
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure();
  double alt = altitudeCalc(temp, pres);

  //Display
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pres);
  Serial.println(" Pa");

  Serial.print("Alt = ");
  Serial.print(alt);
  Serial.println(" m");

  Serial.println();
  delay(500);
}

double altitudeCalc(float nowTemp, float nowPres) {
  float expFac = 0.1902256;  // 1/5.257
  float absTemp = nowTemp + 273.15;
  float perPres = PressureZero / nowPres;
  double expCalc = pow(perPres, expFac);
  double highCalc = ((expCalc - 1) * absTemp) / 0.0065;

  return highCalc;
}