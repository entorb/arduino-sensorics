/*
Class for powering WS2812 LED Ring

TODO:
pinMode(PIN, OUTPUT);
PIN as class parameter

*/
#include "Arduino.h"

#include "TM_Device_Class.h"
#include "TM_LED_Ring_Class.h"
#include "TM_Helper.h"

#include <Adafruit_NeoPixel.h>

// #define PIN 15
// #define NUMPIXELS 8

TM_LED_Ring_Class::TM_LED_Ring_Class(const uint8_t pin_data, const uint8_t this_num_pixels, const bool v) : TM_Display_Device_Class(v), my_pixels(this_num_pixels, pin_data, NEO_GRB + NEO_KHZ800)
{
  num_pixels = this_num_pixels;

  pinMode(pin_data, OUTPUT);
  my_pixels.begin();
  my_pixels.clear();
  my_pixels.setBrightness(8);
}

void TM_LED_Ring_Class::setPixelColor(uint16_t px, uint32_t color)
{
  if (verbose)
  {
    Serial.print("px: ");
    Serial.println(px);
    Serial.print("color: ");
    Serial.println(color);
  }
  my_pixels.clear();
  my_pixels.setPixelColor(px, color);
  my_pixels.show();
}

void TM_LED_Ring_Class::displayValue(const float value)
{
  const uint8_t num_px_to_activate = tm_helper_value_to_category(value, value_min, value_max, num_pixels);
  // currently using the same amount of colors as num_pixels, this might be changed
  uint32_t my_color = color_scale[num_px_to_activate];

  my_pixels.clear();
  for (int i = 0; i <= num_px_to_activate; i++)
  {
    my_pixels.setPixelColor(i, my_color);
  }
  my_pixels.show();
}