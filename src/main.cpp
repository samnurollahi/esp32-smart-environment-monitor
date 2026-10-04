#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define WARN_LED_PIN 23
#define SENSOR_TEMP_PIN 4
#define LDR_PIN 12

enum update
{
  LED,
  OLED,
  LDR,
  DS18B20
};

OneWire oneWire(SENSOR_TEMP_PIN);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

unsigned long prevLdr = 0;
unsigned long prevOled = 0;
unsigned long prevTemp = 0;
int temp = 0;
int ldr = 0;

float readTemp();
int readLdr();
void logicLed();
void logicOled();
void updateFunc();

void setup()
{
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
  pinMode(WARN_LED_PIN, OUTPUT);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(WARN_LED_PIN, 0);
}

void loop()
{
  updateFunc();
}

void updateFunc()
{
  unsigned long now = millis();

  if (now - prevLdr >= 200)
  {
    prevLdr = now;

    readLdr();
  }

  if (now - prevOled >= 100)
  {
    prevOled = now;

    logicOled();
  }

  if (now - prevTemp >= 1000)
  {
    prevTemp = now;

    readTemp();
    logicLed();
  }
}

float readTemp()
{
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  return temp;
};
int readLdr()
{
  ldr = analogRead(LDR_PIN);
  ldr = map(ldr, 0, 4095, 0, 100);
  return ldr;
}

void logicLed()
{
  if (temp < 25)
  {
    ledcWrite(0, 0);
  }
  else if (temp > 25 && temp < 30)
  {
    ledcWrite(0, 76);
  }
  else if (temp > 30 && temp < 35)
  {
    ledcWrite(0, 153);
  }
  else if (temp > 35)
  {
    ledcWrite(0, 256);
  }
}
void logicOled()
{
  String text = "";

  oled.clearDisplay();

  oled.setCursor(34, 0);
  oled.print("ENVIRONMENT");

  oled.setCursor(3, 15);
  text = "TEMP: " + String(temp) + " C";
  oled.print(text);

  oled.setCursor(3, 30);
  text = "LIGHT: " + String(temp) + " %";
  oled.print(text);

  oled.display();
}