#include <LCD-I2C.h>
#define trigger 10
#define echo 11
#define motor 8
#define buzzer 12

LCD_I2C lcd(0x27, 16, 2);

float time=0,distance=0;
int temp=0; 

void setup()

{
 lcd.begin();
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(motor, OUTPUT);
 pinMode(buzzer, OUTPUT);

 lcd.print("  Water Level ");
 lcd.setCursor(0,1);
 lcd.print("   Indicator  ");

 delay(2000);

}

void loop()

{

 lcd.clear();
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);

 delayMicroseconds(10);

 digitalWrite(trigger,LOW);

 delayMicroseconds(2);

 time=pulseIn(echo,HIGH);

 distance=time*340/20000;

 lcd.clear();
 lcd.print("Water Space In ");
 lcd.setCursor(0,1);
 lcd.print("Tank Level: ");
 lcd.print(distance);
 lcd.print("Cm");

 delay(2000);

 if(distance<12 && temp==0)

 {
     digitalWrite(motor, LOW);
     digitalWrite(buzzer, HIGH);

     lcd.clear();
     lcd.print("Water Tank Full ");
     lcd.setCursor(0,1);
     lcd.print("Stop Pumping");

     delay(2000);

     digitalWrite(buzzer, LOW);

     delay(3000);

     temp=1;

 }

  else if(distance<12 && temp==1)

 {

     digitalWrite(motor, LOW);
 for (int positionCounter = 0; positionCounter < 29; positionCounter++) 
  {
      lcd.scrollDisplayRight();
      lcd.clear();
      lcd.print("Water Tank Full ");
      lcd.setCursor(0,1);
      lcd.print("Stop Pumping");
      delay(150);
    }
    
     delay(5000);

 }

 else if(distance>30)

 {

   digitalWrite(motor, HIGH);

   lcd.clear();
    for (int positionCounter = 0; positionCounter < 29; positionCounter++) 
      {
      lcd.scrollDisplayRight();
      lcd.print("Water Level is LOW");
      lcd.setCursor(0,1);
      lcd.print("Start Pumping");
      delay(150);
    }
   
   delay(5000);

   temp=0;

 }

}