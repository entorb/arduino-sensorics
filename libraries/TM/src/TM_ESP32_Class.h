/*
Class for EPS32 Microcontroller 
*/

#ifndef TM_ESP32_CLASS_H
#define TM_ESP32_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

class TM_ESP32_Class : public TM_Device_Class
{
public:
  // constructor
  TM_ESP32_Class(const bool verbose = false);
  // variables
  // functions
  void underclocking();
  void normalclocking();
  void printSpeed();

private:
};
#endif
