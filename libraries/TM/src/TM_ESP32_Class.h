/*
  TM_ESP32_Class.h - Library for Connection to Sensor BME280 (Temp, Humidity, Pressure) via I2C
*/

#ifndef TM_ESP32_CLASS_H
#define TM_ESP32_CLASS_H

#include "TM_Device_Class.h"

class TM_ESP32_Class : public TM_Device_Class
{
public:
  // constructor
  TM_ESP32_Class();
  // variables
  // functions
  void underclocking();
  void normalclocking();
  void printSpeed();

private:
};
#endif
