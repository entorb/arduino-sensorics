/*
Class of Templates for Connection to OLED Displays
Thanks to Gerhard for converting into template!

TODO: int -> uint8_t
*/

#ifndef TM_OLED_CLASS_H
#define TM_OLED_CLASS_H

#include <Arduino.h>
#include "TM_Device_Class.h"
#include "TM_Helper.h"

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

template <class U8G2, uint16_t x, uint16_t y>
class TM_OLED_Class : public TM_Display_Device_Class
{
public:
  // constructor
  TM_OLED_Class(const bool verbose = false);
  // functions
  void init();
  void drawStr(const char *);
  void drawInt(const uint16_t);
  void drawBarChart(const float);
  void appendValueToBarChart(const float);
  void drawFrame();
  void ensure_wake();
  void ensure_sleep();
  void draw_alternating_barchart_and_value(const float);
  void setBarChartRange(const float, const float);

  // TODO: this is not overwritten by children

private:
  U8G2 my_u8g2;
  uint16_t barchart_data[x];
  // variables
  bool last_was_barchart = false; // alternate between bar and int chart
};

typedef TM_OLED_Class<U8G2_SSD1306_128X64_NONAME_F_HW_I2C, 128, 64> TM_OLED_128x64_Class;
typedef TM_OLED_Class<U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C, 128, 32> TM_OLED_128x32_Class;

// Initialisierungsliste
template <class U8G2, uint16_t px_x, uint16_t px_y>
TM_OLED_Class<U8G2, px_x, px_y>::TM_OLED_Class(const bool this_verbose) : TM_Display_Device_Class("OLED", this_verbose), my_u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
{
  // barchart_data[px_x] = {0}; // initialize with all with 0
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::init()
{
  TM_Device_Class::init();
  my_u8g2.begin();
  my_u8g2.clearBuffer();
  my_u8g2.setFont(u8g2_font_inb19_mf); // https://github.com/olikraus/u8g2/wiki/fntlistall
  // my_u8g2.setFont(u8g2_font_ncenB08_tr); // https://github.com/olikraus/u8g2/wiki/fntlistall
  my_u8g2.setFontPosTop();     // setFontPosTop() , setFontPosBaseline() , setFontPosCenter() , setFontPosBottom()
  my_u8g2.setFontDirection(0); // 0..3

  // u8g2_font_inb19_mf: bbox = 16, max height = 31
  // my_u8g2.setFontRefHeightExtendedText(); //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontrefheightextendedtext
  //Serial.println(sizeof(barchart_data) / sizeof(barchart_data[0]));
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::drawStr(const char *text)
{
  // my_u8g2.nextPage();
  my_u8g2.clearBuffer();
  my_u8g2.drawStr(8, 7, text);
  my_u8g2.sendBuffer();
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::drawInt(const uint16_t value)
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
  // my_u8g2.nextPage();
  my_u8g2.clearBuffer();
  my_u8g2.drawStr(8, 7, text);
  my_u8g2.sendBuffer();
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::setBarChartRange(const float barchart_min, const float barchart_max)
{
  setValueRange(barchart_min, barchart_max);
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::appendValueToBarChart(const float value_to_append)
{
  uint16_t value_to_append_px = tm_helper_value_to_category(value_to_append, value_min, value_max, px_y);

  // shift array to left
  for (uint16_t i = 0; i < px_x - 1; i++)
  { // ends at px_x - 2
    barchart_data[i] = barchart_data[i + 1];
  }

  // append new value
  barchart_data[px_x - 1] = value_to_append_px;
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::drawBarChart(const float value_to_append)
{
  appendValueToBarChart(value_to_append);

  // draw the barchart
  my_u8g2.clearBuffer();
  for (uint16_t i = 0; i < px_x; i++)
  {
    // drawLine (x0,y0, x1,y1)
    my_u8g2.drawLine(i, px_y - 1, i, px_y - 1 - barchart_data[i]);
  }
  my_u8g2.sendBuffer();
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::draw_alternating_barchart_and_value(const float value_to_append)
{
  if (last_was_barchart)
  {
    last_was_barchart = false;
    drawInt(value_to_append);
  }
  else
  {
    last_was_barchart = true;
    drawBarChart(value_to_append);
  }
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::drawFrame()
{
  // draw rectangular frame
  my_u8g2.clearBuffer();
  my_u8g2.drawLine(0, 0, 0, px_y - 1);
  my_u8g2.drawLine(px_x - 1, 0, px_x - 1, px_y - 1);
  my_u8g2.drawLine(0, 0, px_x - 1, 0);
  my_u8g2.drawLine(0, px_y - 1, px_x - 1, px_y - 1);
  my_u8g2.sendBuffer();
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::ensure_wake()
{
  if (sleeping == true)
  {
    TM_Display_Device_Class::ensure_wake();
    my_u8g2.sleepOff();
  }
}

template <class U8G2, uint16_t px_x, uint16_t px_y>
void TM_OLED_Class<U8G2, px_x, px_y>::ensure_sleep()
{
  if (sleeping == false)
  {
    TM_Display_Device_Class::ensure_sleep();
    my_u8g2.sleepOn();
  }
}

#endif
