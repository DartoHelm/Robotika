#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(7,DHT11);

const int ledpin=8;

void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();

  pinMode(ledpin, OUTPUT);
}

void loop(){
  float humidity=dht.readHumidity();
  float temperature=dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("Suhu: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Kelembaban: ");
  lcd.print(humidity);
  lcd.print("%");

  if(temperature>30.0){
    digitalWrite(ledpin, HIGH);
  } else {
    digitalWrite(ledpin, LOW);
  }
  delay(2000);
}
