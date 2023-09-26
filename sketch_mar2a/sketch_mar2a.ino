#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define trigPin 13
#define echoPin 12



LiquidCrystal_I2C lcd(0x27, 16, 2);
int counter = 0;
int inside = 0;
int outside = 0;
int currentState1 = 0;
int previousState1 = 0;
int currentState2 = 0;
int previousState2 = 0;


void setup()
{
// initialize the LCD
lcd.init();
//Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop()
{
lcd.setCursor(0, 0);
lcd.print("IN: "); 
lcd.setCursor(4, 0);
lcd.print(inside);

lcd.setCursor(8, 0);
lcd.print("OUT: ");
lcd.setCursor(13, 0);
lcd.print(outside);

if(counter == 0)
{
  lcd.setCursor(0, 1);
  lcd.print("No Cattle inside");
}
else
{
  lcd.setCursor(0, 1);
  lcd.print("Total Inside: ");
  lcd.setCursor(14, 1);
  lcd.print(counter);
}


long duration, distance;

digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance <= 9)
{
  currentState1 = 1;
}
else
{
  currentState1 = 0;
}
delay(100);
if(currentState1 != previousState1)
{
      if(currentState1 == 1)
    {
      counter = counter + 1;
    }
    lcd.setCursor(14, 1);
    lcd.print(counter);
    inside = inside +1;
}
lcd.setCursor(4, 0);
lcd.print(inside);
if (distance > 9 && distance <= 18)
{
  currentState2 = 1;
}
else 
{
  currentState2 = 0;
}
delay(100);
if(currentState2 != previousState2 && counter>=1)
{
    if(currentState2 == 1 && counter>0)
    {
    counter = counter - 1;
    }
    lcd.setCursor(14, 1);
    lcd.print(counter);
    outside = outside +1;
    
}
lcd.setCursor(13, 0);
lcd.print(outside);
if(counter == 0)
{
  lcd.setCursor(0, 1);
  lcd.print("no People");
}
else
{
  lcd.setCursor(14, 1);
  lcd.print(counter);
}
lcd.clear();
}