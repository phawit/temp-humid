#include <EEPROM.h>
#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>
#include <ESP8266WiFiMulti.h>
#include "DHT.h"
#include <time.h>
#include <LiquidCrystal_I2C.h>

#define ssid "setting" //"setting"
#define pass "abcd1234"
#define FIREBASE_HOST "temp-humid-ca49e.firebaseio.com"    //"mutiwifi-4871a.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyDpEDb13yIOHp55aEQqH07ud5C-jrNMdUo" //"dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"
#define LED_BUILTIN 2
#define DHTPIN D3    
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321,DHT11
#define LINE_TOKEN "GFnji208GsM4cFYncTAOi8gzZF6MpwiExEr83PSoCgc"


ESP8266WiFiMulti wifiMulti;
LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);

float temp,humid,hic;

char ssid1[32];
char pass1[32];
int pub;
int dst = 0;
int n = 0;
int rain;

time_t now = time(nullptr);
struct tm* newtime = localtime(&now);
String tmpNow = "";
int timezone = 7;
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";
String Sun = "%E2%98%80%EF%B8%8F";
String Moon = "%F0%9F%8C%9C";
String day;
String flag;  // w:     g:     y:          r:       black:  
String fla;
String water;  // 1/2   1
int train;  //20 30 45 50
int rest; //10 15 30 40
String sta; // rain :  %F0%9F%8C%A8
String x = "%E2%9B%B0"; //
String White = "%F0%9F%8F%B3";
String Green = "%F0%9F%87%B8%F0%9F%87%A6";
String Yellow = "%F0%9F%94%B8";
String Red = "%F0%9F%9A%A9";
String Black = "%F0%9F%8F%B4";  
String Rain = "%E2%9B%88";
String Br = "%F0%9F%94%86";

void Line_Notify(String message) ;
String message;

void writeEEPROM(int startAdr, int laenge, char* writeString) {
  EEPROM.begin(512); 
  yield();
  Serial.println();
  Serial.print("writing EEPROM: "); 
  for (int i = 0; i < laenge; i++)
    {
      EEPROM.write(startAdr + i, writeString[i]);
      Serial.print(writeString[i]);
    }
  EEPROM.commit();
  EEPROM.end();           
}

void readEEPROM(int startAdr, int maxLength, char* dest) {
  EEPROM.begin(512);
  delay(10);
  for (int i = 0; i < maxLength; i++)
    {
      dest[i] = char(EEPROM.read(startAdr + i));
    }
  EEPROM.end();    
  Serial.print("ready reading EEPROM:");
  Serial.println(dest);
}

void clearEEPROM(int startAdr, int laenge) {
  EEPROM.begin(512); 
  yield();
  Serial.println();
  Serial.print("clearing EEPROM: ");
  for (int i = 0; i < laenge; i++)
    {
      EEPROM.write(startAdr + i, 0);
    }
  EEPROM.commit();
  EEPROM.end();           
}

void calTemp(){
  
  float humidX = dht.readHumidity();
  float tempX = dht.readTemperature();
  
  
  if (isnan(humidX) || isnan(tempX)) {
    Serial.println("Failed to read from DHT sensor!");    
    
  }
  else{
    humid = humidX;
    temp = tempX;
  }
  
  hic = dht.computeHeatIndex(temp, humid, false);

  if(hic < 27){       flag = White;  fla = "White";   water = "1/2"; train = 60; rest = 0; }
  else if(hic <= 32){ flag = Green;  fla = "Green";   water = "1/2"; train = 50; rest = 10; }
  else if(hic <= 39){ flag = Yellow; fla = "Yellow";  water = "1";   train = 45; rest = 15; }
  else if(hic <= 51){ flag = Red;    fla = "Red";     water = "1";   train = 30; rest = 30; }
  else {              flag = Black;  fla = "Black";   water = "1";   train = 20; rest = 40; }

  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *C ");  
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(" %\n");

  //********---Rain---****************************************************************************

  if(rain > 945) { n = 0; sta = Br; }
  if(rain < 900) { sta = Rain; }
  
  rain = analogRead(A0);
  Serial.print("\tRain: ");  Serial.println(rain); 

  if(n==0){
    if(rain < 930) {  
      Serial.println("Raining : ");  
      Line_Notify("..%E0%B8%AB%E0%B8%99%E0%B9%88%E0%B8%A7%E0%B8%A2%E0%B8%9D%E0%B8%B6%E0%B8%81%E0%B8%9E%E0%B8%B1%E0%B8%99.%E0%B8%99%E0%B8%A3..%0A%E2%9B%88%E2%9B%88%E2%9B%88It%27s%20raining%20%E2%9B%88%E2%9B%88%E2%9B%88");
      n=1;
      }
  }    

  

}

void pubFirebase(){
  Firebase.setFloat("humid", humid);
  Firebase.setFloat("temp", temp);
  Firebase.setFloat("hic", hic);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["humid"] = humid;
  root["temp"] = temp;
  root["hic"] = hic;
  root["time"] = NowString();
  root["day"] = NowString2();
  root["rain"] = rain;
  String name = Firebase.push("logDHT", root);
}

String NowString() {
   
  now = time(nullptr); 
  tm* newtime = localtime(&now);
  tmpNow = "";
  //tmpNow += " ";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
 
  int t = int(newtime->tm_min);
  if(t < 10){
    tmpNow +="0" + String(newtime->tm_min);
  }
  else{
    tmpNow += String(newtime->tm_min);
  }

  if(int((newtime->tm_hour) >= 19 ) || (int(newtime->tm_hour) >= 0 && int(newtime->tm_hour) <= 6))
    {  day = Moon;     }
  else if(int(newtime->tm_hour) >= 0 && int(newtime->tm_hour) <= 6){ day = Moon;    }
  else { day = Sun; }

  return tmpNow;
  
}

String NowString2() {
  
  now = time(nullptr);
  tm* newtime = localtime(&now);
  tmpNow = "";
  tmpNow += String(newtime->tm_mday);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "-";
  tmpNow += String(newtime->tm_year + 1900 + 543);   
  return tmpNow;
  
}

void pubLCD(){
  lcd.clear();
  Serial.println(NowString() + " "+ NowString2()); lcd.setCursor(0, 0); lcd.print(NowString2() + " " + NowString());
  Serial.print("Temp: ");    Serial.print(temp);   lcd.setCursor(0, 1); lcd.print("Temp  : "); lcd.print(temp);
  Serial.print("\tHumid: "); Serial.print(humid);  lcd.setCursor(0, 2); lcd.print("Humid : "); lcd.print(humid); 
  Serial.print("\tFlag: ");  Serial.print(fla);    lcd.setCursor(0, 3); lcd.print("Flag  : "); lcd.print(fla);
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  readEEPROM(0,32,ssid1);
  readEEPROM(32,32,pass1);
  Serial.println(ssid1);
  Serial.println(pass1);
  wifiMulti.addAP(ssid, pass);
  wifiMulti.addAP(ssid1, pass1);

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());
  
}

void Line_Notify(String message) {
  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);
    
  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}

void loop() {

  if(wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
        calTemp();
    }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    pub = Firebase.getInt("pub");
    Serial.print("ssid : ");
    Serial.println(WiFi.SSID());  
    //readEEPROM(0,32,ssid1);
    //readEEPROM(32,32,pass1);
    calTemp();
    pubFirebase();
    Serial.println(NowString() + " "+ NowString2());
    pubLCD();

    Line_Notify("asas");
    delay(10000);
  
  }

 //wait internet and pub = 1 
 if((wifiMulti.run() == WL_CONNECTED)&&(pub==1)) {
  String x = Firebase.getString("ssid1");
  String y = Firebase.getString("pass1");
  
  char a[x.length()+1]; 
  x.toCharArray(a, sizeof(a)); 
  char b[y.length()+1]; 
  y.toCharArray(b, sizeof(b)); 

  //char a[10] = "MyWifi";
  //char b[10] = "abcd1234";
  writeEEPROM(0,32,a);
  writeEEPROM(32,32, b);
  Serial.println("everything saved...");
  readEEPROM(0,32,ssid1);
  readEEPROM(32,32,pass1);
  wifiMulti.addAP(ssid1, pass1);
  Serial.println("Update wifi");
  //delay(1000);
  for (int i=0; i <= 5; i++){
   digitalWrite(LED_BUILTIN, LOW);
   delay(50);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(50);
  } 
  Firebase.setInt("pub", 0);
  
 }
 
  
}

