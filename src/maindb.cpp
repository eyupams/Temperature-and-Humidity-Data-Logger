#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <RTClib.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal.h>

//set the DHT pin
const int DHT_SENSOR_PIN = 13;

//init rtc clock
RTC_DS1307 RTC;

//init dht component
DHT dht(DHT_SENSOR_PIN, DHT11);

//init lcd display
LiquidCrystal lcd(7,8,9,10,11,12);

void setup() {
    Serial.begin(9600);
    dht.begin();
    lcd.begin(16,2);
    lcd.print("Temp:  Humidity:");
    Wire.begin();
    RTC.begin();
    RTC.adjust(DateTime(__DATE__, __TIME__));
}

void showTime() {
  DateTime now = RTC.now();
  Serial.print(now.day());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.year());
  Serial.print(' ');

  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();
  delay(1000);
}

void loop() {
  
  Serial.print(dht.readTemperature()); //Store date on Excel
  Serial.print("\t");
  Serial.println(dht.readHumidity()); //Store date on Excel
  //showTime();
  lcd.setCursor(0,1);
  float h = dht.readHumidity();
  //float t = dht.readTemperature(true); //show fahrenheit
  float f = dht.readTemperature();

  if (isnan(h) || isnan(f)) {
    lcd.print("ERROR");
  } else {
    lcd.print(f);
    lcd.setCursor(7,1);
    lcd.print(h);
  }

  delay(30000); //update readings
}