/*
Class for reading BH1750 Light Sensor

Based on Advanced BH1750 library usage example
*/

#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_BH1750_Class.h"

#include <Wire.h>
#include <BH1750.h>

TM_BH1750_Class::TM_BH1750_Class(const bool this_verbose) : TM_Sensor_Device_Class("BH1750", this_verbose)
{
}

void TM_BH1750_Class::init()
{
  TM_Sensor_Device_Class::init();
  // TM: this needs to be done here, not in constructore
  // my_lightMeter(0x23);
  Wire.begin(); // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  my_lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
}

float TM_BH1750_Class::read()
{
  lux = my_lightMeter.readLightLevel();
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.print("Light = ");
    Serial.print(lux);
    Serial.println(" lx");
  }
  return lux;
}
