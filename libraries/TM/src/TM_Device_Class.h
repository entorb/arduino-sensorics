/*
Abstract Class that all other device classes inherit from
*/

#ifndef TM_DEVICE_CLASS_H
#define TM_DEVICE_CLASS_H

#include "Arduino.h"

class TM_Device_Class
{
public:
  // constructor
  TM_Device_Class(const bool verbose = true);
  // functions
  void setVerbose(bool);
  void init();
  // variables
  bool verbose = false;
  // Idea:
  // char devicename[8];

private:
};
#endif
