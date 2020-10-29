/*
  TM_Sensor_Class.cpp - My Sensor interface
*/
#include "TM_Sensor_Class.h"

TM_Sensor_Class::TM_Sensor_Class()
{
  verbose = false;
}

void TM_Sensor_Class::init()
{
}

void TM_Sensor_Class::setVerbose(bool myVerbose)
{
  verbose = myVerbose;
}