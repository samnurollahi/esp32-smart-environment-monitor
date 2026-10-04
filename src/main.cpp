#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_TEMP_PIN 4

OneWire oneWire(SENSOR_TEMP_PIN);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

unsigned long prev = 0;
int temp = 0;

float readTemp();

void setup() {
  Serial.begin(9600);

  sensors.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(34, 0);
  oled.print("ENVIRONMENT");
  oled.display();


  pinMode(SENSOR_TEMP_PIN, INPUT);
}


void loop() {
  Serial.println(readTemp());
}


float readTemp() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}



