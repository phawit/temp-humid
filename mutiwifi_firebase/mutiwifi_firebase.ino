#include <EEPROM.h>
#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>
#include <ESP8266WiFiMulti.h>
#include "DHT.h"
#include <time.h>
#include <LiquidCrystal_I2C.h>

#define ssid "setting"
#define pass "abcd1234"
#define FIREBASE_HOST "temp-humid-ca49e.firebaseio.com" //"mutiwifi-4871a.firebaseio.com"
#define FIREBASE_AUTH "Ow0tnLgQGJnOv8X4GEwdj2H8RucR9iHEEGrQUeSJ"  //"dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"
#define DHTPIN D3    
#define DHTTYPE DHT22  

char wifi_ssid[32];
char wifi_pass[32];
char wifi_ssid1[32];
char wifi_pass1[32];
float temp,humid,hic;
String flag,water;
int train,rest,b;

int timezone = 7 * 3600;                    //ตั้งค่า TimeZone ตามเวลาประเทศไทย
int dst = 0;   
time_t now = time(nullptr);
struct tm* newtime = localtime(&now);
String tmpNow = "";

ESP8266WiFiMulti wifiMulti;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

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

  if(hic < 27){       flag = "White";   water = "1/2"; train = 60; rest = 0; }
  else if(hic <= 32){ flag = "Green";   water = "1/2"; train = 50; rest = 10; }
  else if(hic <= 39){ flag = "Yellow";  water = "1";   train = 45; rest = 15; }
  else if(hic <= 51){ flag = "Red";     water = "1";   train = 30; rest = 30; }
  else {              flag = "Black";   water = "1";   train = 20; rest = 40; }


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
  Serial.println(flag);
  Serial.println(water);
  Serial.println(train);
  Serial.println(rest);

}

String NowString() {
  
  now = time(nullptr);
  tm* newtime = localtime(&now);
  tmpNow = "";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  
  int t = int(newtime->tm_min);
  if(t < 10){
    tmpNow +="0" + String(newtime->tm_min);
  }
  else{
    tmpNow += String(newtime->tm_min);
  }
  
  //tmpNow += String(newtime->tm_min);
  
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
  Serial.println(NowString() + " "+ NowString2()); lcd.setCursor(0, 0); lcd.print(NowString2() + "     " + NowString());
  Serial.print("Temp: ");    Serial.print(temp);   lcd.setCursor(0, 1); lcd.print("Temp  : "); lcd.print(temp);
  Serial.print("\tHumid: "); Serial.print(humid);  lcd.setCursor(0, 2); lcd.print("Humid : "); lcd.print(humid); 
  Serial.print("\tFlag: ");  Serial.print(flag);   lcd.setCursor(0, 3); lcd.print("Flag  : "); lcd.print(flag);
  
}

void doIn14()
{ 
  Serial.println("interrupt14,,,,,");
  lcd.backlight();
  b = 1;
  
  //lcd.noBacklight(); 
   
}
  
void setup() {

  pinMode(2, INPUT);  //Switch
  pinMode(14, INPUT);  //Switch 
  attachInterrupt(14, doIn14,RISING);
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.begin(9600);
  lcd.begin();
  //lcd.backlight();
  dht.begin();
  delay(100);
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");

  strcat(wifi_ssid, ssid);
  strcat(wifi_pass, pass);
  writeEEPROM(0,32,wifi_ssid);//32 byte max length
  writeEEPROM(32,32,wifi_pass);//32 byte max length

  readEEPROM(64,32,wifi_ssid1);
  readEEPROM(96,32,wifi_pass1);
  wifiMulti.addAP(wifi_ssid1, wifi_pass1);
  wifiMulti.addAP(ssid, pass);
  lcd.noBacklight();

}

void loop() {
  if(b==1){
    delay(3000);
    lcd.noBacklight();
    b = 0;
    
  }
  
  calTemp();
  pubLCD();

  if(wifiMulti.run() == WL_CONNECTED) {
     Serial.println("WiFi connected");
     Serial.print("Wifi: ");
     Serial.println(WiFi.SSID());
     Firebase.setInt("id/A03/sta", 1);
     while (!time(nullptr)) {
      Serial.print(".");
      delay(1000);
     }

     

//     calTemp();
//
//     pubLCD();
     
     Serial.println(NowString());
     Serial.println(NowString2());
     Firebase.setFloat("id/A03/humid", humid);
     Firebase.setFloat("id/A03/temp", temp);
     Firebase.setFloat("id/A03/hic", hic);
     Firebase.setString("id/A03/flag", flag);
     Firebase.setString("id/A03/time", NowString());
     Firebase.setString("id/A03/date", NowString2());
     StaticJsonBuffer<200> jsonBuffer;
     JsonObject& root = jsonBuffer.createObject();
     root["humid"] = humid;
     root["temp"] = temp;
     root["hic"] = hic;
     root["flag"] = flag;
     root["time"] = NowString();
     root["date"] = NowString2();
     String name = Firebase.push("id/A03/logDHT", root);
  
     int pub = Firebase.getInt("id/A03/pub");    
     Serial.println(pub);
     
     if(pub==1){
      Serial.println("pub set to 1");
      
      clearEEPROM(64,32);
      clearEEPROM(96,32);
      readEEPROM(64,32,wifi_ssid1);
      readEEPROM(96,32,wifi_pass1);

      String x = Firebase.getString("id/A03/ssid");    //.c_str();
      String y = Firebase.getString("id/A03/pass");    //.c_str();
      char ssid1[x.length()+1]; 
      x.toCharArray(ssid1, sizeof(ssid1)); 
      char pass1[y.length()+1]; 
      y.toCharArray(pass1, sizeof(pass1)); 
      strcat(wifi_ssid1, ssid1);
      strcat(wifi_pass1, pass1);
     
      writeEEPROM(64,32,wifi_ssid1);//10 byte max length
      writeEEPROM(96,32,wifi_pass1);//16 byte max length
  
      Serial.println("everything saved...");
      readEEPROM(64,32,wifi_ssid1);
      readEEPROM(96,32,wifi_pass1);
      wifiMulti.addAP(wifi_ssid1, wifi_pass1);
      Serial.println(wifi_ssid1);
      Serial.println(wifi_pass1);

      //set pub = 0
      Firebase.setInt("pub", 0);
      
     }
 
  }
  else{
    Serial.println("NO INTERNET");
    readEEPROM(0,32,wifi_ssid);
    readEEPROM(32,32,wifi_pass);
    readEEPROM(64,32,wifi_ssid1);
    readEEPROM(96,32,wifi_pass1);
    //calTemp();
   
  }

  delay(1000);
}
