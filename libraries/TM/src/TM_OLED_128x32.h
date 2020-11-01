/*
  TM_OLED_128x32.h - Library for Connection to my InfluxDB
*/

#ifndef TM_OLED_128x32_H
#define TM_OLED_128x32_H

#include "TM_Device_Class.h"

class TM_OLED_128x32_Class : public TM_Device_Class
{
public:
  // constructor
  TM_OLED_128x32_Class();
  // functions
  void init();
  void drawStr(const int, const int, const char *);

private:
  int barchart_min;
  int barchart_max;
  int barchart_line;
};

#endif
