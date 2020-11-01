/*
  TM_OLED_128x32_Class.h - Library for Connection to OLED Displays
*/

#ifndef TM_OLED_128x32_CLASS_H
#define TM_OLED_128x32_CLASS_H

#include "TM_Device_Class.h"

#include <Arduino.h>

#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

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
  //variables
  // static U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C my_u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

private:
  //variables
  const static unsigned int px_x = 128;
  const static unsigned int px_y = 32;
  unsigned int barchart_min;
  unsigned int barchart_max;
  unsigned int barchart_data[px_x]; //TODO: is there a way of defining the array length upon creation of object from class
  bool last_was_barchart = false;   // alternate between bar and int chart
};

#endif
