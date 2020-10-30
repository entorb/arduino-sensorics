/*
  TM_ESP32.cpp - Library for Connection to Sensor BME280 (Temp, Humidity, Pressure) via I2C
*/

#include "TM_Device_Class.h"
#include "TM_ESP32_Class.h"

#include <Arduino.h>       // for Serial
#include "esp32-hal-cpu.h" // for: power saving
// setCpuFrequencyMhz(80); // for
// Serial.println( getCpuFrequencyMhz() );

TM_ESP32_Class::TM_ESP32_Class() : TM_Device_Class()
{
}

void TM_ESP32_Class::underclocking()
{
  if (verbose == true)
  {
    Serial.print(F("ESP32 underclocked to "));
  }
  setCpuFrequencyMhz(80); // 240, 160, 80
  if (verbose == true)
  {
    Serial.print(getCpuFrequencyMhz());
    Serial.println("MHz");
  }
}
