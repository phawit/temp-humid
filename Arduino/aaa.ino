/*
 * https://notify-bot.line.me/my/ 
 * http://meyerweb.com/eric/tools/dencoder/ 
Tools
1.NodeMCU V2
2.DHT22--D3
3.RainSensor--A0
4.LCD20x4.SDA--D2
         .SCL--D1
         .VCC--5V (only)
5.LED--D0,GND
6.TouchSwitch--D5,D4       
             --3.3V
             --GND
DHT22------------->NodeMCU-->LCD20X4 (BackLight On-Off from Switch)
GoogleSheet(LED)-->       -->LED
Switch(interrupt)->       -->Line (Every 8,10,12,14,16,21 o'clock)
                          -->Line (When Rain is Coming!)
                          -->GoogleScrip >> GoogleSheet (every 0,15,30,45 min)
*/

#include <ESP8266WiFi.h>
//#include "HTTPSRedirect.h"
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <time.h>

#define DHTPIN D3    
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321,DHT11
#define LINE_TOKEN "euXafEAEwoJLylFSNmB2e4qXEryZXqE4yBfTVB6OBpD"

//"v2yeZTB17hbxcDZ6BHx6xgr2iLGb74UfjeQFrQ59nTo"  //ภูมิากาศ = "%E0%B8%A0%E0%B8%B9%E0%B8%A1%E0%B8%B4%E0%B8%AD%E0%B8%B2%E0%B8%81%E0%B8%B2%E0%B8%A8%F0%9F%8F%9C"

DHT dht(DHTPIN, DHTTYPE);
float temp,humid,hic;

void Line_Notify(String message) ;
String message;

String Sun = "%E2%98%80%EF%B8%8F";
String Moon = "%F0%9F%8C%9C";
int rain,n,k,p,b=0,e=0;
String day;

int dst = 0;

time_t now = time(nullptr);
struct tm* newtime = localtime(&now);
String tmpNow = "";

//LiquidCrystal_I2C lcd(0x3F, 20, 4);
LiquidCrystal_I2C lcd(0x27, 20, 4);

int timezone = 7;
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";

const char* ssid = "MyWifi";      //"first";  //"MyWifi";  //------------------------------------edit
const char* password = "abcd1234";  //------------------------------------------edit

//const char* host = "script.google.com";
//const char* googleRedirHost = "script.googleusercontent.com";
//https://script.google.com/macros/s/AKfycbz-ZwxNXXVEPBBkHRt_DXb4LDTfQoszbJ28mNS2CSEo6WjCHiY/exec
//const char *GScriptId = "AKfycbz-ZwxNXXVEPBBkHRt_DXb4LDTfQoszbJ28mNS2CSEo6WjCHiY";  //-------------------------------------------edit
//const int httpsPort = 443;
// echo | openssl s_client -connect script.google.com:443 |& openssl x509 -fingerprint -noout
//const char* fingerprint = "D1 58 71 3D 71 54 34 86 50 2A DF FE 2C 74 85 50 82 20 95 C3";  //--------------------------------------------------------edit
//String url_x = String("/macros/s/") + GScriptId + "/exec?value=Hello";
//String url_x = String("/macros/s/") + GScriptId + "/exec";
//String url3 = String("/macros/s/") + GScriptId + "/exec?read";
//String url = url_x + "?tag=" + String(humid) + "&value=" + String(temp);

void setup() {

  dht.begin();

  k = 984;
  p = 0;
  n=1;

  pinMode(D0, OUTPUT);  //LED
  pinMode(2, INPUT);  //Switch
  pinMode(14, INPUT);  //Switch 
  
  //attachInterrupt(2, doIn2,RISING);
  //attachInterrupt(14, doIn14,FALLING);
  attachInterrupt(14, doIn14,RISING);


  lcd.begin();
  lcd.backlight();
     
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  lcd.setCursor(0, 0); lcd.print("WiFi connected");
  Serial.println("IP address: ");    lcd.setCursor(0, 1); lcd.print("IP address: ");  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());

  //configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  configTime(timezone * 3600, dst,"pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());
  lcd.clear();
/*
  HTTPSRedirect client(httpsPort);
  Serial.print("Connecting to ");  
  Serial.println(host);

  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client.connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }
  
  Serial.flush();
  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  } 
  Serial.flush();
  if (client.verify(fingerprint, host)) {
    Serial.println("Certificate match.");
  } else {
    Serial.println("Certificate mis-match");
  }
*/
  Serial.println("==============================================================================");
    
  delay(500);
  lcd.noBacklight();
  lcd.clear();
 
}

void loop() {

  if(b==1){
    delay(3000);
    lcd.noBacklight();
    b = 0;
    
  }

  if(e==3){
    Line_Notify(message); Serial.println("line notify");
    e = 0;
  }
  e = 0;
  

  
   
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
 
//*************---LCD---***************************************************************

  lcd.clear();
  Serial.println(NowString() + " "+ NowString2()); lcd.setCursor(0, 0); lcd.print(NowString2() + " " + NowString());
  Serial.print("Temp: ");    Serial.print(temp);   lcd.setCursor(0, 1); lcd.print("Temp  : "); lcd.print(temp);
  Serial.print("\tHumid: "); Serial.print(humid);  lcd.setCursor(0, 2); lcd.print("Humid : "); lcd.print(humid); 
  Serial.print("\tFlag: ");  Serial.print(fla);    lcd.setCursor(0, 3); lcd.print("Flag  : "); lcd.print(fla);
  
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
     
//********--LINE--**************************************************************************** 
    
    String messageA = "%E0%B8%AB%E0%B8%99%E0%B9%88%E0%B8%A7%E0%B8%A2%E0%B8%9D%E0%B8%B6%E0%B8%81%E0%B8%97%E0%B8%AB%E0%B8%B2%E0%B8%A3%E0%B9%83%E0%B8%AB%E0%B8%A1%E0%B9%88%E0%B8%9E%E0%B8%B1%E0%B8%99.%E0%B8%99%E0%B8%A3.%E0%B8%A3%E0%B8%A3.%E0%B8%AA." + 
               sta +'\n'+
               NowString2() + NowString() + day +
              "\n" + x + "%E0%B8%AA%E0%B8%B1%E0%B8%8D%E0%B8%8D%E0%B8%B2%E0%B8%93%E0%B8%98%E0%B8%87%3A%20" + flag +
              "\n" + x + "%E0%B8%AD%E0%B8%B8%E0%B8%93%E0%B8%AB%E0%B8%A0%E0%B8%B9%E0%B8%A1%E0%B8%B4%3A%20" + temp + "%20%C2%B0C" +
              "\n" + x + "%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B8%8A%E0%B8%B7%E0%B9%89%E0%B8%99%E0%B8%AA%E0%B8%B1%E0%B8%A1%E0%B8%9E%E0%B8%B1%E0%B8%97%E0%B8%98%E0%B9%8C%3A%20" + humid + "%20%25" +
              "\n" + x + "%E0%B8%9B%E0%B8%A3%E0%B8%B4%E0%B8%A1%E0%B8%B2%E0%B8%93%E0%B8%99%E0%B9%89%E0%B8%B3%E0%B8%94%E0%B8%B7%E0%B9%88%E0%B8%A1%3A%20" + water + "%20%E0%B8%A5%E0%B8%B4%E0%B8%95%E0%B8%A3%2F%E0%B8%8A%E0%B8%A1.";
    String messageB;
    if(fla == "White"){  messageB = "\n" + x + "%E0%B8%9D%E0%B8%B6%E0%B8%81%E0%B9%84%E0%B8%94%E0%B9%89%E0%B8%95%E0%B9%88%E0%B8%AD%E0%B9%80%E0%B8%99%E0%B8%B7%E0%B9%88%E0%B8%AD%E0%B8%87";  }
    else{
      messageB = "\n" + x + "%E0%B9%81%E0%B8%99%E0%B8%B0%E0%B8%99%E0%B8%B3%E0%B9%83%E0%B8%AB%E0%B9%89%E0%B8%9D%E0%B8%B6%E0%B8%81%3A%20" + train + "%20%E0%B8%99%E0%B8%B2%E0%B8%97%E0%B8%B5" "  " + 
                 "\n   " + "%20%20%E0%B8%9E%E0%B8%B1%E0%B8%81%3A%20" + rest + "%20%E0%B8%99%E0%B8%B2%E0%B8%97%E0%B8%B5";
    }
    
    message = messageA + messageB;
    
       
//       message = "100student" + sta +'\n'+
//               NowString2() + NowString() + day +
//              "\n" + x + "Flag : " + flag +
//              "\n" + x + "Temp : " + temp + " c" +
//             "\n" + x + "Humid : " + humid +
//              "\n" + x + "Water : " + water + " l/h" +
//             "\n" + x + "Training : " + train + "  " + "  Rest : " + rest + " min";

       
   int h = int(newtime->tm_hour);
   int mm = int(newtime->tm_min);
   int ss = int(newtime->tm_sec);
  
   if(((h==8)||(h==10)||(h==12)||(h==14)||(h==16)||(h==21))&&(mm==0))
     {   
       if(k!= mm){  Line_Notify(message);  Serial.println("Line_Notify");  k=mm;  }      
     } 
             
   if(mm==5){ k=23; }  

   delay(1000);
//*******---Google---*******************************************************************************
/*
  String url = url_x + "?tag=" + String(humid) + "&value=" + String(temp) + "&rain=" + String(rain);
 
  HTTPSRedirect client(httpsPort);
  if(!client.connected())
    { client.connect(host, httpsPort);  } 
  
  client.printRedir(url3, host, googleRedirHost);
  

  if((mm==7)||(mm==22)||(mm==37)||(mm==52)){  p=0; }
   
  if(p==0){   
    if((mm==0)||(mm==15)||(mm==30)||(mm==45)){
       client.printRedir(url, host, googleRedirHost);
       p=1;
    }   
  }  
*/
  
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
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  
  client.print(req);  
  delay(20);

  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }    
  }
  
}

String NowString() {
   
  now = time(nullptr); 
  tm* newtime = localtime(&now);
  tmpNow = "";
  tmpNow += " ";
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

/*
void doIn2()
{  
  Serial.println("interrupt2,,,,,");
  lcd.backlight();
  b = 1;
  
}
*/

void doIn14()
{ 
  Serial.println("interrupt14,,,,,");
  lcd.backlight();
  b = 1;
  e++;
  //lcd.noBacklight(); 
   
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

