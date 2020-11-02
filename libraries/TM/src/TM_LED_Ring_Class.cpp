/*
  TM_LED_Ring_Class.cpp - Library for powering WS2812 LED Ring
  */
#include <Adafruit_NeoPixel.h>

#include "TM_Device_Class.h"
#include "TM_LED_Ring_Class.h"

#include "Arduino.h" // for Serial.println()

#define PIN 15
#define NUMPIXELS 8

TM_LED_Ring_Class::TM_LED_Ring_Class() : TM_Device_Class(), my_pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800)
{
  my_pixels.begin();
  my_pixels.clear();
  my_pixels.setBrightness(16);
}

void TM_LED_Ring_Class::init()
{
  // my_pixels.setBrightness(brightness);
}

void TM_LED_Ring_Class::setValueRange(const float min, const float max)
{
  value_min = min;
  value_max = max;
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
  // calc a number of led pixels to activate, based on value with respect to value_min and value_max

  unsigned int num_px_to_activate;
  if (value <= value_min)
  { // 1 on
    num_px_to_activate = 0;
  }
  else if (value >= value_max)
  { // -> all on
    num_px_to_activate = num_pixels - 1;
  }
  else
  {
    // convert value to number of pixels
    const float value_rel = value - value_min;
    const float range_rel = value_max - value_min;
    num_px_to_activate = num_pixels * (value_rel / range_rel);
  }
  if (verbose)
  {
    Serial.print("value: ");
    Serial.println(value);
    Serial.print("num_px_to_activate: ");
    Serial.println(num_px_to_activate);
  }
  uint32_t my_color = color_scale[num_px_to_activate];

  my_pixels.clear();
  for (int i = 0; i <= num_px_to_activate; i++)
  {
    // currently using the same amount of colors as num_pixels, this might be changed
    my_pixels.setPixelColor(i, my_color);
  }
  my_pixels.show();
}