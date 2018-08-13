// Coding By IOXhop : www.ioxhop.com

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// สร้างออปเจ็ค server เพิ่มเริ่มใช้งาน Web Server ที่พอร์ต 80
ESP8266WebServer server(80);

void setup(void){
  // ใช้โหมดทำตัวเป็น AP
  WiFi.mode(WIFI_AP);

  // เมื่อเข้ามาที่ลิ้ง /
  server.on("/", []() {
    // ** รูปแบบ **
    //      server.send(int httpcode, String type, String data); 
    // ** ค่าพารามิเตอร์ **
    //  -> (int) htmlcode - โค้ด http (ศึกษาเพิ่มเติมที่ https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)
    //  -> (String) type - ชนิดของเอกสารที่ส่งกลับ
    //  -> (String) data - ข้อมูลที่ส่งกลับ
    // ** ค่าส่งกลับ **
    //      ไม่มี
    server.send(200, "text/html", "<h1>Hello, world !</h1>");
  });

  server.begin(); // เปิดการใช้งาน Web Server
}

void loop() {
  server.handleClient(); // ตรวจสอบว่ามีคนเรียกหน้าเว็บแล้วหรือยัง (เอาไว้ในฟังก์ชั่น loop() เสมอ)
}
