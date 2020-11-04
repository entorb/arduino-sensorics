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
  // void println(); no, too much efford to overload all the different types of Serial.println()
  // variables
  bool verbose = false;
  // char devicename[8]; no uses for this,as overwriting print is too much efford

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
  TM_Display_Device_Class(const bool verbose = true);
  // functions
  void setValueRange(const float value_min, const float value_max);
  // variables
  float value_min = 400;
  float value_max = 1000;

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
  TM_Sensor_Device_Class(const bool verbose = true);
  // functions
  // variables

private:
};
#endif