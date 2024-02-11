#include <Wire.h>

#define RTC_addr 0x68

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }
  Serial.println("Start");


  //write time to DS1307
  //(sec, min, hour, week, day, month, year)
  write_RTC(0, 35, 18, 3, 11, 2, 24);
}

void loop() {

  // check the function
  // Serial.println("int is 59");
  // Serial.println(int_to_BCD(59));
  // Serial.println(BCD_to_int(int_to_BCD(59)));

  // read rtc time
  // format is BCD
  byte sec_r = read_RTC(0x00);
  byte min_r = read_RTC(0x01);
  byte hour_r = read_RTC(0x02);
  // byte day_r = read_RTC(0x03);
  byte date_r = read_RTC(0x04);
  byte month_r = read_RTC(0x05);
  byte year_r = read_RTC(0x06);

  // convert BCD to int
  int sec = BCD_to_int(sec_r);
  int min = BCD_to_int(min_r);
  int hour = BCD_to_int(hour_r);
  // int day = BCD_to_int(day_r); // san, mon...
  int date = BCD_to_int(date_r);
  int month = BCD_to_int(month_r);
  int year = BCD_to_int(year_r);

  Serial.print(year);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(date);
  Serial.print("/");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(min);
  Serial.print(":");
  Serial.println(sec);

  delay(1000);
}

byte read_RTC(byte addr) {
  Wire.beginTransmission(RTC_addr);
  Wire.write(addr);
  Wire.endTransmission(false);
  Wire.requestFrom(RTC_addr, 1, true);
  byte data = Wire.read();
  return data;
}

void write_RTC(int sec, int min, int hour, int week, int day, int month, int year) {
  // DS1307 memory is BCD
  // int to BCD
  byte sec_w = int_to_BCD(sec);
  byte min_w = int_to_BCD(min);
  byte hour_w = int_to_BCD(hour);
  byte week_w = int_to_BCD(week);  // week is date
  byte day_w = int_to_BCD(day);
  byte month_w = int_to_BCD(month);
  byte year_w = int_to_BCD(year);

  // update RTC time
  Wire.beginTransmission(RTC_addr);
  Wire.write(0x00);  // register header addr
  Wire.write(sec_w);
  Wire.write(min_w);
  Wire.write(hour_w);
  Wire.write(week_w);
  Wire.write(day_w);
  Wire.write(month_w);
  Wire.write(year_w);
  Wire.endTransmission();
}

int int_to_BCD(byte data) {
  // e.g. data = 59
  uint8_t ones = data % 10;           // 9
  uint8_t tens = (data - ones) / 10;  // 5
  uint8_t BCD = (tens << 4) | ones;   // 89 = 0x59

  return BCD;
}

int BCD_to_int(byte BCD) {
  // e.g. BCD =  0x89(59, B01011001)
  uint8_t ones = BCD & B1111;      // 9
  uint8_t tens = (BCD >> 4) * 10;  // 50
  uint8_t data = tens + ones;

  return data;
}
