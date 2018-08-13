#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Arduino UNO => PIN 4 = SCL, PIN 5 = SDA
// NodeMCU Dev Kit => D1 = SCL, D2 = SDA
//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  //delay(3000);
  //lcd.noBacklight();
  lcd.print("Hello LCD Line 1");
        lcd.setCursor(0, 1);
  lcd.print("Hello LCD Line 2");
        lcd.setCursor(0, 2);
  lcd.print("Hello LCD Line 3");
        lcd.setCursor(0, 3);
  lcd.print("Hello LCD Line 4");
  
}

void loop()
{
  // Do nothing here...
}
