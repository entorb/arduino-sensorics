/*
  TM_MH-Z19_Class.h - Library for reading a MH-Z19 CO2 sensor
*/

#ifndef TM_MH_Z19_Class_h
#define TM_MH_Z19_Class_h

#include "MHZ19.h"
class TM_MH_Z19_Class
{
public:
  // constructor
  TM_MH_Z19_Class(bool verbose);
  // variables
  void init();
  int read_values();

private:
  bool verbose;
  MHZ19 myMHZ19; // Constructor for library
};
#endif
