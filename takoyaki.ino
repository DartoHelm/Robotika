#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define echoPin 7
#define trigPin 6
int ledPin   = 10;
int servoPin = 9;
int buzzer = 8;

Servo Servo1;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Servo1.attach(servoPin);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  delay(2000);
  lcd.clear();
}
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 50 || distance <= 0){
    lcd.setCursor(0,0);
    lcd.print("Out of range");
    lcd.setCursor(0,1);
    lcd.print("No Object Found");
    delay(1000);
    lcd.clear();
    digitalWrite(ledPin, LOW);
    noTone(buzzer);
    Servo1.write(0);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Object is ");
    lcd.print(distance);
    lcd.print(" cm");
    digitalWrite(ledPin, HIGH);
    tone(buzzer, 500);
    Servo1.write(180);
    lcd.setCursor(0, 1);
    lcd.print("Arm Moved");
    delay(1000);
    lcd.clear();
  }
}
