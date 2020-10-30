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
  TM_MH_Z19_Class();
  // functions
  void init();
  int read_values();
  // variables

private:
  MHZ19 myMHZ19; // Constructor for library
};
#endif
