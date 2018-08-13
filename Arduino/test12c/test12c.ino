
//https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  
  lcd.begin();
}

void loop()
{
  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cursor blink");
      lcd.setCursor(0, 1);
      lcd.print("Cursor blink");
      lcd.setCursor(0, 2);
      lcd.print("Cursor blink");
      lcd.setCursor(0, 3);
      lcd.print("12345678901234567890");
 

    delay(1000);
    lcd.noBacklight();
    
    delay(1000);
    lcd.backlight();
    
}
