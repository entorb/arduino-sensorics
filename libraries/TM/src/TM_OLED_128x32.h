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
  void drawStr(const char *);
  void drawInt(const unsigned int);
  void drawBarchart(const float);
  void drawAltBarchartOrInt(const float);
  void setBarchartRange(const float, const float);

private:
  const static unsigned int px_x = 128;
  const static unsigned int px_y = 32;
  unsigned int barchart_min;
  unsigned int barchart_max;
  unsigned int barchart_data[px_x]; //TODO: is there a way of defining the array length upon creation of object from class
  bool last_was_barchart = false;   // alternate between bar and int chart
};

#endif
