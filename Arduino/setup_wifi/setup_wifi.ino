#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>

#define FIREBASE_HOST "mutiwifi-4871a.firebaseio.com"
#define FIREBASE_AUTH "dIpneH3aKMRgA3nMm36g7SnVGY2QfqRP4BnXXez2"

void setup() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
  int z = findMyhome();
  Serial.print("aaaaaaaaaaaaaaaaaa::::: ");
  Serial.println(z);

  const char* ssid;    
  const char* pass;
  
  if(z==1){
  ssid     = "setting";
  pass = "abcd1234";
  WiFi.begin(ssid, pass); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }    
  }
  else{ Serial.println("not found myhome"); }  

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("WiFi connected");  
    String ssid1 = Firebase.getString("ssid1");    //.c_str();
    String pass1 = Firebase.getString("pass1");    //.c_str();
    Serial.print(ssid1);
    Serial.print(pass1);
    WiFi.disconnect();
    Serial.print("wifi disconnect");
       
    String x = ssid1;  //"Myhome";
    String y = pass1;  //"abcd1234";

    char a[x.length()+1]; 
    x.toCharArray(a, sizeof(a)); 
    char b[y.length()+1]; 
    y.toCharArray(b, sizeof(b)); 

    WiFi.begin(a,b);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    if(WiFi.status() == WL_CONNECTED){
      Serial.print("WiFi connect to : ");
      Serial.println(WiFi.SSID()); 
    }  
  }

  
}  


  
void loop() {
  Serial.println(WiFi.SSID());   
  delay(500);
}

int findMyhome(){
  int p;
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    for (int i = 0; i < n; ++i)
    {   
      if(WiFi.SSID(i)=="Myhome"){ Serial.println("found Myhome"); return 1;  }
      delay(10);
    }
    
  }
  delay(5000);
  return 0;


  
}

