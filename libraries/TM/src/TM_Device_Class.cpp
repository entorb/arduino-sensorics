/*
  TM_Device_Class.cpp - My Device interface
*/
#include "TM_Device_Class.h"

TM_Device_Class::TM_Device_Class()
{
  verbose = false;
}

void TM_Device_Class::init()
{
}

void TM_Device_Class::setVerbose(bool v)
{
  verbose = v;
}
