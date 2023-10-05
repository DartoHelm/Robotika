#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define echoPin 7
#define trigPin 6
int ledPin   = 10;
int buzzer = 8;
int servoPin = 9;

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
  lcd.write("Welcome");
  delay(5000);
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

  if (distance >= 100 || distance <= 0){
    Serial.println("Out of range");
    lcd.clear();
    lcd.print("No Object Found");
    delay(500);
    lcd.clear();
    digitalWrite(ledPin, LOW);
    noTone(buzzer);
    Servo1.write(0);
  }
  else {
    Serial.print("Object is ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println(" far from the machine");
    digitalWrite(ledPin, HIGH);
    tone(buzzer, 1000);
    Servo1.write(180);
    Serial.println("Arm Moved");
    lcd.write("Object Found");
    lcd.setCursor(0, 1);
    lcd.write("Arm Moved");
    delay(7000);
    lcd.clear();
  }
}