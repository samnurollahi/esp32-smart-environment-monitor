#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_TEMP_PIN 4
#define LDR_PIN 12

OneWire oneWire(SENSOR_TEMP_PIN);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

unsigned long prev = 0;
int temp = 0;
int ldr = 0;

float readTemp();
int readLdr();

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
  pinMode(LDR_PIN, INPUT);
}


void loop() {


}


float readTemp() {
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  return temp;
};
int readLdr() {
  ldr = analogRead(LDR_PIN);
  return ldr;
}