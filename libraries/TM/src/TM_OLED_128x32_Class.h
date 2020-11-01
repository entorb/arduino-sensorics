/*
  TM_OLED_128x32_Class.h - Library for Connection to OLED Displays
*/

#ifndef TM_OLED_128x32_CLASS_H
#define TM_OLED_128x32_CLASS_H

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

class TM_OLED_128x32_Class : public TM_OLED_Class
{
public:
  U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C my_u8g2;
  // constructor
  TM_OLED_128x32_Class();
  // functions

private:
  //variables
  const static unsigned int px_x = 128;
  const static unsigned int px_y = 32;
  unsigned int barchart_data[px_x]; //TODO: is there a way of defining the array length upon creation of object from class
};

#endif
