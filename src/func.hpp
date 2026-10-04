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