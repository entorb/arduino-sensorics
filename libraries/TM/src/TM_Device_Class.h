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
  TM_Device_Class(const char devicename[], const bool verbose = true);
  // functions
  void setVerbose(bool);
  void printDeviceName();
  void init();
  // void println(); no, too much effort to overload all the different types of Serial.println()

  // variables
  // used in verbose: Serial.print() to identify the sending device
  char devicename[8];
  // if set to true -> print stuff to Serial.print()
  bool verbose;

private:
};
#endif

#ifndef TM_DEVICE_DISPLAY_CLASS_H
#define TM_DEVICE_DISPLAY_CLASS_H

#include "Arduino.h"

// this is a sub-class of Device_Class, that stores min, max value
class TM_Display_Device_Class : public TM_Device_Class
{
public:
  // constructor
  TM_Display_Device_Class(const char devicename[], const bool verbose = true);
  // functions
  void ensure_wake();
  void ensure_sleep();
  void setValueRange(const float value_min, const float value_max);
  // variables
  bool sleeping = false;
  float value_min = 400;
  float value_max = 1000;
  // 3 colors for 600 values -> blue for 600-800

private:
};
#endif

#ifndef TM_DEVICE_SENSOR_CLASS_H
#define TM_DEVICE_SENSOR_CLASS_H

#include "Arduino.h"

// this is a sub-class of Device_Class, that stores min, max value
class TM_Sensor_Device_Class : public TM_Device_Class
{
public:
  // constructor
  TM_Sensor_Device_Class(const char devicename[], const bool verbose = true);
  // functions
  // variables

private:
};
#endif
