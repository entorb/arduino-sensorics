/*
  TM_MH-Z19_Class.h - Library for reading a MH-Z19 CO2 sensor
*/

#ifndef TM_MH_Z19_CLASS_H
#define TM_MH_Z19_CLASS_H

#include "TM_Device_Class.h"

#include "MHZ19.h"

class TM_MH_Z19_Class : public TM_Device_Class
{
public:
  // constructor
  // HardwareSerial mySerial_Class(1); // (ESP32 Example) create device to MH-Z19 serial
  TM_MH_Z19_Class();
  // functions
  void init();
  int read_values();
  // variables

private:
  MHZ19 myMHZ19;
  HardwareSerial mySerial_Class;
};
#endif
