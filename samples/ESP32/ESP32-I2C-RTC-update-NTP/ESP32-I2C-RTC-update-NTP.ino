#include <Wire.h>
#define RTC_address 0x68

uint8_t REG_table[7];

void setup() {
  Wire.begin();
  Serial.begin(115200);

  Serial.println("start");


  Wire.beginTransmission(RTC_address);
  Wire.write(0x00);  //Register 先頭アドレス
  Wire.write(0x00);  //second
  Wire.write(0x36);  //minute
  Wire.write(0x20);  //hour
  Wire.write(0x04);  //week
  Wire.write(0x24);  //day
  Wire.write(0x12);  //month
  Wire.write(0x22);  //year
  Wire.endTransmission();
}

void loop() {
  //一つずつ読む場合
  byte sec_d = read_rtc(0x00);
  byte min_d = read_rtc(0x01);
  byte hour_d = read_rtc(0x02);
  byte day_d = read_rtc(0x04);
  byte month_d = read_rtc(0x05);


  int sec = dec_to_int(sec_d);
  int min = dec_to_int(min_d);
  int hour = dec_to_int(hour_d);
  int day = dec_to_int(day_d);
  int month = dec_to_int(month_d);

  Serial.print(sec);
  Serial.print("秒, ");
  Serial.print(min);
  Serial.print("分, ");
  Serial.print(hour);
  Serial.print("時, ");
  Serial.print(day);
  Serial.print("日, ");
  Serial.print(month);
  Serial.print("月");




  //一括で読む場合
  /*
    byte k[20];
    read_rtc_multibyte(k, 0x00, 7);
    for (int i = 0; i < 7; i++) {
    Serial.print(k[i]);
    Serial.print(", ");
    }

    int sec = dec_to_int(k[0]);
    int min = dec_to_int(k[1]);
    int hour = dec_to_int(k[2]);
    int day = dec_to_int(k[4]);
    int month = dec_to_int(k[5]);

    Serial.print(sec);
    Serial.print("秒, ");
    Serial.print(min);
    Serial.print("分, ");
    Serial.print(hour);
    Serial.print("時, ");
    Serial.print(day);
    Serial.print("日, ");
    Serial.print(month);
    Serial.print("月");
  */


  Serial.println("");

  delay(1000);
}

int dec_to_int(byte dec) {
  int data;
  data = (dec >> 4) * 10 + (dec & 0x0F);
  return data;
}
void write_rtc(byte add, byte data) {
  Wire.beginTransmission(RTC_address);
  Wire.write(add);
  Wire.write(data);
  Wire.endTransmission();
}
byte read_rtc(byte add) {
  byte k = 0;
  Wire.beginTransmission(RTC_address);
  Wire.write(add);
  Wire.endTransmission();
  Wire.requestFrom(RTC_address, 1);
  while (Wire.available()) {
    k = Wire.read();
  }
  return k;
}


void read_rtc_multibyte(byte *array1, byte add, int num) {
  Wire.beginTransmission(RTC_address);
  Wire.write(add);
  Wire.endTransmission();
  Wire.requestFrom(RTC_address, num);
  int i = 0;
  while (Wire.available()) {
    array1[i] = Wire.read();
    i++;
  }
}
