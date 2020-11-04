/*
Class for reading a MH-Z19 CO2 sensor
*/

#ifndef TM_MH_Z19_CLASS_H
#define TM_MH_Z19_CLASS_H

#include <Arduino.h>
#include "TM_Device_Class.h"

#include "MHZ19.h"

class TM_MH_Z19_Class : public TM_Device_Class
{
public:
  // constructor
  TM_MH_Z19_Class(const uint8_t pin_rx, const uint8_t pin_tx, const bool verbose = false);
  // functions
  int read_values();
  // variables

private:
  // variables
  MHZ19 myMHZ19;
  HardwareSerial mySerial;
  uint8_t _pin_rx;
  uint8_t _pin_tx;
};
#endif
