#include <EEPROM.h>
#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>

#define ssid "setting"
#define pass "abcd1234"
//#define FIREBASE_HOST "mutiwifi-4871a.firebaseio.com"
//#define FIREBASE_AUTH "dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"
#define FIREBASE_HOST "temp-humid-ca49e.firebaseio.com" //"mutiwifi-4871a.firebaseio.com"
#define FIREBASE_AUTH "Ow0tnLgQGJnOv8X4GEwdj2H8RucR9iHEEGrQUeSJ"  //"dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"

char wifi_ssid[32];
char wifi_pass[32];
char wifi_ssid1[32];
char wifi_pass1[32];


//startAdr: offset (bytes), writeString: String to be written to EEPROM
void writeEEPROM(int startAdr, int laenge, char* writeString) {
  EEPROM.begin(512); //Max bytes of eeprom to use
  yield();
  Serial.println();
  Serial.print("writing EEPROM: ");
  //write to eeprom 
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
  
void setup() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.begin(9600);
  delay(100);

  WiFi.begin(ssid, pass); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }    
  Serial.print("connected defult wifi");

  //const char* ssid1 = "JoleenAlien";    
  //const char* pass1 = "1234567890";

  //String ssid1 = Firebase.getString("ssid1");    //.c_str();
  //String pass1 = Firebase.getString("pass1");    //.c_str();
  String x = Firebase.getString("ssid1");    //.c_str();
  String y = Firebase.getString("pass1");    //.c_str();
  char ssid1[x.length()+1]; 
  x.toCharArray(ssid1, sizeof(ssid1)); 
  char pass1[y.length()+1]; 
  y.toCharArray(pass1, sizeof(pass1)); 

  WiFi.disconnect();
  WiFi.begin(ssid1,pass1);
  Serial.print("connected router wifi");
  
  strcat(wifi_ssid, ssid);
  strcat(wifi_pass, pass);
  strcat(wifi_ssid1, ssid1);
  strcat(wifi_pass1, pass1);

  writeEEPROM(0,32,wifi_ssid);//32 byte max length
  writeEEPROM(32,32,wifi_pass);//32 byte max length
  writeEEPROM(64,32,wifi_ssid1);//10 byte max length
  writeEEPROM(96,32,wifi_pass1);//16 byte max length
  /*85 byte saved in total?*/  
  Serial.println("everything saved...");
  readEEPROM(0,32,wifi_ssid);
  readEEPROM(32,32,wifi_pass);
  readEEPROM(64,32,wifi_ssid1);
  readEEPROM(96,32,wifi_pass1);
  WiFi.disconnect();
  WiFi.begin(wifi_ssid1,wifi_pass1);
  Serial.println("xxxxxxxxxx");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop");
  Serial.println(WiFi.SSID());
  delay(1000);
  
  String x = Firebase.getString("ssid1");    //.c_str();
  String y = Firebase.getString("pass1");    //.c_str();
  char ssid1[x.length()+1]; 
  x.toCharArray(ssid1, sizeof(ssid1)); 
  char pass1[y.length()+1]; 
  y.toCharArray(pass1, sizeof(pass1));
  strcat(wifi_ssid, ssid);
  strcat(wifi_pass, pass);
  strcat(wifi_ssid1, ssid1);
  strcat(wifi_pass1, pass1);

  Serial.println(ssid);
  Serial.println(ssid1);
//  S/erial.println(wifi_ssid1);
  
  writeEEPROM(0,32,wifi_ssid);//32 byte max length
  writeEEPROM(32,32,wifi_pass);//32 byte max length
  writeEEPROM(64,32,wifi_ssid1);//10 byte max length
  writeEEPROM(96,32,wifi_pass1);//16 byte max length
  /*85 byte saved in total?*/  
  Serial.println("everything saved...");
  readEEPROM(0,32,wifi_ssid);
  readEEPROM(32,32,wifi_pass);
  readEEPROM(64,32,wifi_ssid1);
  readEEPROM(96,32,wifi_pass1);
}
