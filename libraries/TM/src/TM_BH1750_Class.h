/*
Class for reading BH1750 Light Sensor

Based on Advanced BH1750 library usage example
*/

#ifndef TM_BH1750_CLASS_H
#define TM_BH1750_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

#include <Wire.h>
#include <BH1750.h>

class TM_BH1750_Class : public TM_Sensor_Device_Class
{
public:
  // constructor
  TM_BH1750_Class(const bool verbose = false);
  // variables
  // functions
  void init();
  float read();

private:
  // variables
  BH1750 my_lightMeter;
  float lux;
};
#endif
