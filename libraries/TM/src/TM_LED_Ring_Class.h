/*
Class for powering WS2812 LED Ring
*/

#ifndef TM_LED_RING_CLASS_H
#define TM_LED_RING_CLASS_H

#include "Arduino.h"

#include <Adafruit_NeoPixel.h>

#include "TM_Device_Class.h"

class TM_LED_Ring_Class : public TM_Display_Device_Class
{
public:
  // constructor
  Adafruit_NeoPixel my_pixels;
  TM_LED_Ring_Class(const uint8_t pin_data, const uint8_t num_pixels, const bool verbose = false);
  // functions
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
  byte _num_pixels = 8;
  // byte brightness = 32; // 0..255

  // currently as many colors as pixels, but this could be changed
};
#endif
