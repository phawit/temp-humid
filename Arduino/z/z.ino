#include <EEPROM.h>
#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>
#include <ESP8266WiFiMulti.h>

#define ssid "settings"
#define pass "abcd1234"
#define FIREBASE_HOST "mutiwifi-4871a.firebaseio.com"
#define FIREBASE_AUTH "dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"
#define LED_BUILTIN 2


ESP8266WiFiMulti wifiMulti;

char ssid1[32];
char pass1[32];
int pub;

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

void setup() {
  Serial.begin(9600);
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  //strcat(ssid1, "iPhone");
  //strcat(pass1, "abcd1234");
  //writeEEPROM(0,32,ssid1);
  //writeEEPROM(32,32, pass1);
  //Serial.println("everything saved...");
  readEEPROM(0,32,ssid1);
  readEEPROM(32,32,pass1);
  Serial.println(ssid1);
  Serial.println(pass1);
  wifiMulti.addAP(ssid, pass);
  //wifiMulti.addAP("setting", "abcd1234");
  wifiMulti.addAP(ssid1, pass1);
  
}

void loop() {

  if(wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
    }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    pub = Firebase.getInt("pub");
    Serial.print("ssid : ");
    Serial.println(WiFi.SSID());  
    readEEPROM(0,32,ssid1);
    readEEPROM(32,32,pass1); 
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

