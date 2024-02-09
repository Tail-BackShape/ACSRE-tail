#include <SPI.h>

const int SCK_Pin = 4;   //SPI0 SCK
const int MOSI_Pin = 5;  //SIP0 Tx
const int MISO_Pin = 6;  //SPI0 Rx
const int Cs_Pin = 7;    //SPI0 Cs

SPISettings  spisttings(10000000, MSBFIRST, SPI_MODE3);

void setup() {
  Serial.begin(115200);


  //setup SPI
  SPI.setCS(Cs_Pin);
  SPI.setRX(MISO_Pin);
  SPI.setSCK(SCK_Pin);
  SPI.setTX(MOSI_Pin);
  SPI.begin();
  pinMode(Cs_Pin, OUTPUT);
  digitalWrite(Cs_Pin, HIGH);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void beginSpi(int Cs_Pin) {
  SPI.beginTransaction(spisttings);
  digitalWrinte(Cs_Pin, LOW);  // CSピンをLOWにする
}

void endSpi(int Cs_Pin) {
  digitalWrite(Cs_Pin, HIGH);  // CSピンをHIGHにする
  SPI.endTransaction();
}