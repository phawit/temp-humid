
#include <ESP8266WiFi.h>
#include <time.h>

const char* ssid = "MyWifi";
const char* password = "abcd1234";

int timezone = 7;
int dst = 0;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void loop() {
  time_t newtime = time(nullptr);
  //Serial.println(ctime(&now));
  delay(1000);

   int h = int(newtime->tm_hour);
   int mm = int(newtime->tm_min);
   int ss = int(newtime->tm_sec);

   Serial.println(h);

  
}



