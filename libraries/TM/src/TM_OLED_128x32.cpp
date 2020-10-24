/*
  TM_OLED_128x32.cpp - Library for Connection to 128x32 OLED Display
*/
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

#include "TM_OLED_128x32.h"

void TM_OLED_128x32_init()
{
  u8g2.begin();
  u8g2.setFont(u8g2_font_inb19_mf); // https://github.com/olikraus/u8g2/wiki/fntlistall
  // u8g2_font_inb19_mf: bbox = 16, max height = 31
  // u8g2.setFontRefHeightExtendedText(); //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontrefheightextendedtext
  u8g2.setFontPosTop();     // setFontPosTop() , setFontPosBaseline() , setFontPosCenter() , setFontPosBottom()
  u8g2.setFontDirection(0); // 0..3
}

void TM_OLED_128x32_drawStr(int offset_x, int offset_y, char *text)
{
  u8g2.clearBuffer();
  u8g2.drawStr(8, 7, text);
  u8g2.sendBuffer();
}