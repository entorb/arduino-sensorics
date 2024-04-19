/*
Class for EPS32 Microcontroller 
*/

#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_ESP32_Class.h"

#include "esp32-hal-cpu.h" // for: power saving

TM_ESP32_Class::TM_ESP32_Class(const bool this_verbose) : TM_Device_Class("ESP32", this_verbose)
{
}

void TM_ESP32_Class::restart()
{
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.println("Software restart");
  }
  ESP.restart();
}

void TM_ESP32_Class::underclocking()
// Attention: underclocking leeds to problems in Adafruit_NeoPixel
{
  setCpuFrequencyMhz(80); // 240, 160, 80
  if (verbose)
  {
    printSpeed();
  }
}

void TM_ESP32_Class::normalclocking()
{
  setCpuFrequencyMhz(240); // 240, 160, 80
  if (verbose)
  {
    printSpeed();
  }
}

void TM_ESP32_Class::printSpeed()
{
  TM_Device_Class::printDeviceName();
  Serial.print(getCpuFrequencyMhz());
  Serial.println("MHz");
}