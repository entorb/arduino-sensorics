/*
  TM_LED_Ring_Class.h - Library for powering WS2812 LED Ring
*/
#ifndef TM_LED_RING_CLASS_H
#define TM_LED_RING_CLASS_H

#include <Adafruit_NeoPixel.h>

#include "TM_Device_Class.h"

class TM_LED_Ring_Class : public TM_Device_Class
{
public:
  // constructor
  Adafruit_NeoPixel my_pixels;
  TM_LED_Ring_Class();
  // functions
  void init();
  void setValueRange(const float, const float);
  void setPixelColor(const uint16_t, const uint32_t);
  void displayValue(const float);
  // variables
  const uint32_t color_scale[8] = {
      0x00ff00, // green
      0x19e600,
      0x95fc00,
      0xffff00, // yellow
      0xff8700,
      0xcc3300,
      0xe61a00,
      0xff0000 // red
  };

private:
  // variables
  byte num_pixels = 8;
  // byte brightness = 32; // 0..255
  float value_min = 400;
  float value_max = 1200;

  // currently as many colors as pixels, but this could be changed
};
#endif
