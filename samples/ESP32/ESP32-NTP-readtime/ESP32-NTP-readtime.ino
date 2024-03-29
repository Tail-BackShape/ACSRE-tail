#include <WiFi.h>

const char *ssid = "SSID";
const char *password = "PASSWORD";

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (WiFi.begin(ssid, password) != WL_DISCONNECTED)
  {
    ESP.restart();
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  Serial.println("Connected to the WiFi network!");

  configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
}

struct tm timeInfo;
char s[20];

void loop()
{
  getLocalTime(&timeInfo); // tmオブジェクトのtimeInfoに現在時刻を入れ込む
  sprintf(s, " %04d/%02d/%02d %02d:%02d:%02d",
          timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
          timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec); // 人間が読める形式に変換
  delay(1000);
  Serial.println(s); // 時間をシリアルモニタへ出力
}
