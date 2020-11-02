/*
  TM_ESP32.cpp - Library for Connection to Sensor BME280 (Temp, Humidity, Pressure) via I2C
*/

#include "TM_Device_Class.h"
#include "TM_ESP32_Class.h"

#include <Arduino.h>       // for Serial.println()
#include "esp32-hal-cpu.h" // for: power saving

TM_ESP32_Class::TM_ESP32_Class() : TM_Device_Class()
{
}

void TM_ESP32_Class::underclocking()
// Attention: underclocking leeds to problems in Adafruit_NeoPixel
{
  setCpuFrequencyMhz(80); // 240, 160, 80
  if (verbose)
    printSpeed();
}

void TM_ESP32_Class::normalclocking()
{
  setCpuFrequencyMhz(240); // 240, 160, 80
  if (verbose)
    printSpeed();
}

void TM_ESP32_Class::printSpeed()
{
  Serial.print(getCpuFrequencyMhz());
  Serial.println("MHz");
}