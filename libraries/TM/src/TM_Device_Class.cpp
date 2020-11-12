/*
Abstract Class that all other device classes inherit from
*/

#include "Arduino.h"
#include "TM_Device_Class.h"

TM_Device_Class::TM_Device_Class(const bool this_verbose)
{
  verbose = this_verbose;
}

void TM_Device_Class::setVerbose(bool this_verbose)
{
  verbose = this_verbose;
}

void TM_Device_Class::init()
{
}

// this is a sub-class of Device_Class, that additionally stores value_min and value_max as display scale range
TM_Display_Device_Class::TM_Display_Device_Class(const bool v) : TM_Device_Class(v){};

void TM_Display_Device_Class::ensure_wake()
{
  if (verbose)
    Serial.println("Waking display to up");
  sleeping = false;
}

void TM_Display_Device_Class::ensure_sleep()
{
  if (verbose)
    Serial.println("Sending display to sleep");
  sleeping = true;
}

void TM_Display_Device_Class::setValueRange(const float this_value_min, const float this_value_max)
{
  value_min = value_min;
  value_max = value_max;
}

// this is a sub-class of Device_Class, to be later filled with sensor specific code
TM_Sensor_Device_Class::TM_Sensor_Device_Class(const bool v) : TM_Device_Class(v){};
// TODO: add functions, if needed