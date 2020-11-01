/*
  TM_OLED_128x32_Class.cpp - Library for Connection to 128x32 OLED Display
*/
//based on
/*
  HelloWorld.ino
  by
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
*/

#include "TM_Device_Class.h"
#include "TM_OLED_Class.h"
#include "TM_OLED_128x32_Class.h"

#include <Arduino.h>
#include "U8g2lib.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// TODO:
// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C my_u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

TM_OLED_128x32_Class ::TM_OLED_128x32_Class() : TM_OLED_Class(), my_u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
{
  barchart_data[px_x] = {0}; // initialize with all with 0
}
