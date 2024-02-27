void setup() {
  // シリアルポート開始
  Serial.begin(9600);

  Serial1.setTX(0);  // pin 1
  Serial1.setRX(1);  // pin 2
  Serial1.begin(9600);
}

void loop() {
  while (Serial1.available() > 0)
    Serial.write(Serial1.read());
  delay(1);
}
