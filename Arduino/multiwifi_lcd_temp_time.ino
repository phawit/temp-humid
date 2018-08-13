#include<ESP8266WiFi.h>
#include<ESP8266WiFiMulti.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <time.h>

ESP8266WiFiMulti wifimulti;
ESP8266WiFiMulti wifimulti2;

//String ssid1,pass1;

#define FIREBASE_HOST "temp-humid-ca49e.appspot.com"   //"mutiwifi-4871a.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyDpEDb13yIOHp55aEQqH07ud5C-jrNMdUo" //"dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"
#define DHTPIN D3    
#define DHTTYPE DHT22   

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);
float temp,humid,hic;

int timezone = 7 * 3600;                    //ตั้งค่า TimeZone ตามเวลาประเทศไทย
int dst = 0;   
time_t now = time(nullptr);
struct tm* newtime = localtime(&now);
String tmpNow = "";
               

void setup() {
  
  Serial.begin(115200);
  Serial.println();
  wifimulti.addAP("setting","abcd1234");          //SSID2,PASSWORD2

  lcd.begin();
  lcd.backlight();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();

   const char* myssid = Firebase.getString("ssid1").c_str();
      const char* mypass = Firebase.getString("pass1").c_str();

      Serial.print("myssid :: ");  Serial.println(Firebase.getString("ssid1"));
      Serial.print("mypass :: ");  Serial.println(Firebase.getString("pass1"));
  
     // wifimulti.addAP(myssid,mypass);        //SSID1,PASSWORD1
      wifimulti.addAP("MzyWifi","abcd1234");
      Serial.println("mywifi added");

   configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");     //ดึงเวลาจาก Server
   Serial.println("\nWaiting for time");
   while (!time(nullptr)) {
      Serial.print(".");
      delay(1000);
   }
   Serial.println("");
 
 

/*
  const char* myssid = ssid1.c_str();
  const char* mypass = pass1.c_str();

  Serial.print("myssidddddd :: ");  Serial.println(myssid);
  Serial.print("mypasssssss :: ");  Serial.println(mypass);
  
  wifimulti.addAP(myssid,mypass);        //SSID1,PASSWORD1
*/

}

void loop() {
  
  if(wifimulti.run()!=WL_CONNECTED){          //IF NO NETWORK IS  CONNECTED
      Serial.println("waiting for AP");   lcd.setCursor(0, 0); lcd.print("NO wifi");  lcd.clear(); 

      
  }
  else if(wifimulti.run()==WL_CONNECTED){
      Serial.println(WiFi.SSID());   
      //lcd.setCursor(0, 0); lcd.print("wifi connected"); lcd.setCursor(0, 1); lcd.print(WiFi.SSID()); lcd.noBacklight(); 
      delay(1000);
      calTemp();

      //********---Cal_Flag_Train_rest---***************************  
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
  
  if(hic < 27){       flag = White;  fla = "White";   water = "1/2"; train = 60; rest = 0; }
  else if(hic <= 32){ flag = Green;  fla = "Green";   water = "1/2"; train = 50; rest = 10; }
  else if(hic <= 39){ flag = Yellow; fla = "Yellow";  water = "1";   train = 45; rest = 15; }
  else if(hic <= 51){ flag = Red;    fla = "Red";     water = "1";   train = 30; rest = 30; }
  else {              flag = Black;  fla = "Black";   water = "1";   train = 20; rest = 40; }

      //ssid1 = Firebase.getString("ssid1");
      //pass1 = Firebase.getString("pass1");
      //Serial.print("import ssid1 :: ");  Serial.println(ssid1);
      //Serial.print("import pass1 :: ");  Serial.println(pass1);
      //delay(1000);
//       /
       
        Serial.println(NowString());
        Serial.println(NowString2());
              
       delay(1000);
  //*************---LCD---***************************************************************

  lcd.clear();
  Serial.println(NowString() + " "+ NowString2()); lcd.setCursor(0, 0); lcd.print(NowString2() + "     " + NowString());
  Serial.print("Temp: ");    Serial.print(temp);   lcd.setCursor(0, 1); lcd.print("Temp  : "); lcd.print(temp);
  Serial.print("\tHumid: "); Serial.print(humid);  lcd.setCursor(0, 2); lcd.print("Humid : "); lcd.print(humid); 
  Serial.print("\tFlag: ");  Serial.print(fla);    lcd.setCursor(0, 3); lcd.print("Flag  : "); lcd.print(fla);
  
  
     
    
  }

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

}

String NowString() {
  
  now = time(nullptr);
  tm* newtime = localtime(&now);
  tmpNow = "";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  
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


