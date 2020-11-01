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
#include "TM_OLED_128x32_Class.h"

#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// TODO: move into class, but this led to reboots of the Arduino, so research needed
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C my_u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

TM_OLED_128x32_Class ::TM_OLED_128x32_Class() : TM_Device_Class()
{
  barchart_data[px_x] = {0}; // initialize with all with 0
}
void TM_OLED_128x32_Class::init()
{
  my_u8g2.begin();
  my_u8g2.setFont(u8g2_font_inb19_mf); // https://github.com/olikraus/u8g2/wiki/fntlistall
  // u8g2_font_inb19_mf: bbox = 16, max height = 31
  // my_u8g2.setFontRefHeightExtendedText(); //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontrefheightextendedtext
  my_u8g2.setFontPosTop();     // setFontPosTop() , setFontPosBaseline() , setFontPosCenter() , setFontPosBottom()
  my_u8g2.setFontDirection(0); // 0..3
  my_u8g2.clearBuffer();
  //Serial.println(sizeof(barchart_data) / sizeof(barchart_data[0]));
  // draw rectangular frame
  // my_u8g2.drawLine(0, 0, 0, px_y - 1);
  // my_u8g2.drawLine(px_x - 1, 0, px_x - 1, px_y - 1);
  // my_u8g2.drawLine(0, 0, px_x - 1, 0);
  // my_u8g2.drawLine(0, px_y - 1, px_x - 1, px_y - 1);
}

void TM_OLED_128x32_Class::drawStr(const char *text)
{
  my_u8g2.drawStr(8, 7, text);
  my_u8g2.sendBuffer();
}

void TM_OLED_128x32_Class::drawInt(const unsigned int value)
{
  // convert int -> char[]
  // C++17 style
  // std::array<char, 10> str;
  // std::to_chars(str.data(), str.data() + str.size(), 42);
  // C++11 style
  // std::string s = std::to_string(data_mhz_CO2);
  // s += "ppm";
  // char const *text = s.c_str();
  // Arduino Style
  char cstr[16];
  itoa(value, cstr, 10);   /// base 10
  char const *text = cstr; //+ "ppm";  my_u8g2.clearBuffer();
  my_u8g2.clearBuffer();
  my_u8g2.drawStr(8, 7, text);
  my_u8g2.sendBuffer();
}

void TM_OLED_128x32_Class::setBarchartRange(const float min, const float max)
{
  barchart_min = min;
  barchart_max = max;
}

void TM_OLED_128x32_Class::drawBarchart(const float value_to_append)
{
  unsigned int value_to_append_px;

  if (value_to_append <= barchart_min)
  {
    // -> min bar size => 0
    value_to_append_px = 0;
  }
  else if (value_to_append >= barchart_max)
  { // -> max bar size
    value_to_append_px = px_y - 1;
  }
  else
  {
    // convert value_to_append to y-px scale
    const float value_rel = value_to_append - barchart_min;
    const float range_rel = barchart_max - barchart_min;
    value_to_append_px = px_y * (value_rel / range_rel);
  }

  // Serial.print("value: ");
  // Serial.print(value_to_append);
  // Serial.print(" -> ");
  // Serial.print(value_to_append_px);
  // Serial.println("px");

  // shift array to left
  for (unsigned int i = 0; i < px_x - 1; i++)
  { // ends at px_x - 2
    barchart_data[i] = barchart_data[i + 1];
  }

  // append new value
  barchart_data[px_x - 1] = value_to_append_px;

  // draw the barchart
  my_u8g2.clearBuffer();
  for (unsigned int i = 0; i < px_x; i++)
  {
    // drawLine (x0,y0, x1,y1)
    my_u8g2.drawLine(i, px_y - 1, i, px_y - 1 - barchart_data[i]);
  }
  my_u8g2.sendBuffer();
}

void TM_OLED_128x32_Class::drawAltBarchartOrInt(const float value_to_append)
{
  if (last_was_barchart)
  {
    last_was_barchart = false;
    drawInt(value_to_append);
  }
  else
  {
    last_was_barchart = true;
    drawBarchart(value_to_append);
  }
}