float analogValue;
float input_voltage;

void setup()
{
   Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps
   pinMode(LED_BUILTIN,OUTPUT);
   pinMode(A4,INPUT);
   

   

}

void loop()
{
   digitalWrite(LED_BUILTIN,1);
   analogValue = analogRead (A4);
   Serial.println(analogValue);
   delay (1000); 
   input_voltage = (analogValue * 5.0) / 1024.0;
   digitalWrite(LED_BUILTIN,0);
   Serial.println(input_voltage);
   delay(1000);

}
