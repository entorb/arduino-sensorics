/*
  TM_OLED_128x64_Class.h - Library for Connection to OLED Displays
*/

#ifndef TM_OLED_128x64_CLASS_H
#define TM_OLED_128x64_CLASS_H

#include "TM_Device_Class.h"
#include "TM_OLED_Class.h"

#include <U8g2lib.h>

#include <Arduino.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class TM_OLED_128x64_Class : public TM_OLED_Class
{
public:
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C my_u8g2;
  // constructor
  TM_OLED_128x64_Class();
  // functions
  // variables
  const unsigned int px_x = 128;
  const unsigned int px_y = 64;
  unsigned int barchart_data[128];

private:
  // variables
};

#endif
