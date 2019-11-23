#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <RTClib.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal.h>

//define the sensor type
#define DHT_SENSOR_TYPE DHT11

//set the DHT pin
const int DHT_SENSOR_PIN = 13;

//init rtc clock
RTC_DS1307 RTC;

//init dht component
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

//init lcd display
LiquidCrystal lcd(7,8,9,10,11,12);

void initPlxdaq() {
  Serial.println("CLEARDATA"); //clears excel sheet
  Serial.println("LABEL,Date,Time,Temperature,Humidity"); //make headings in sheet
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.print("Temp:  Humidity:");
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  initPlxdaq();
}

void writePlxdaq()
{
    Serial.print("DATA"); //always write "DATA" to Inidicate the following as Data
    Serial.print(","); //Move to next column using a ","

    Serial.print("DATE"); //Store date on Excel
    Serial.print(","); //Move to next column using a ","

    Serial.print("TIME"); //Store date on Excel
    Serial.print(","); //Move to next column using a ","

    Serial.print(dht.readTemperature()); //Store date on Excel
    Serial.print(","); //Move to next column using a ","

    Serial.print(dht.readHumidity()); //Store date on Excel
    Serial.print(","); //Move to next column using a ","

    Serial.println(); //End of Row move to next row

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
  
  writePlxdaq();
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

  delay(60000); //update readings
}