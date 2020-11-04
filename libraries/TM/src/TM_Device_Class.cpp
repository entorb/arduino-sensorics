/*
Abstract Class that all other device classes inherit from
*/

#include "Arduino.h"
#include "TM_Device_Class.h"

TM_Device_Class::TM_Device_Class(const bool v)
{
  verbose = v;
}

void TM_Device_Class::setVerbose(bool v)
{
  verbose = v;
}

void TM_Device_Class::init()
{
}
