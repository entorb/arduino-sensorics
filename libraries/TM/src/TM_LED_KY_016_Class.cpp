/*
Class for powering 3 color RGB LED KY-016
*/

/*
based on "RGBLed.h"

*/

#include "Arduino.h"
#include <analogWrite.h>
// #include "RGBLed.h"

#include "TM_Device_Class.h"
#include "TM_LED_KY_016_Class.h"
#include "TM_Helper.h"

TM_LED_KY_016_Class::TM_LED_KY_016_Class(const uint8_t pin_red, const uint8_t pin_green, const uint8_t pin_blue, const bool v) : TM_Device_Class(v)
{
  _pin_red = pin_red;
  _pin_green = pin_green;
  _pin_blue = pin_blue;

  pinMode(_pin_red, OUTPUT);
  pinMode(_pin_green, OUTPUT);
  pinMode(_pin_green, OUTPUT);
}
void TM_LED_KY_016_Class::setValueRange(const float min, const float max)
{
  value_min = min;
  value_max = max;
}
void TM_LED_KY_016_Class::setColor(const uint32_t rgb, const uint8_t brightness)
{
  // html rgb code to int
  uint8_t red = rgb >> 16;
  uint8_t green = (rgb & 0x00ff00) >> 8;
  uint8_t blue = (rgb & 0x0000ff);
  setColor(red, green, blue, brightness);
}

void TM_LED_KY_016_Class::setColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t brightness)
{
  // brightness 0..255
  analogWrite(_pin_red, (red * brightness / 255));
  analogWrite(_pin_green, (green * brightness / 255));
  analogWrite(_pin_blue, (blue * brightness / 255));
}

void TM_LED_KY_016_Class::displayValue(const float value)
{
  const uint8_t num_colors = sizeof(color_scale) / sizeof(color_scale[0]);
  uint8_t color_index = tm_helper_value_to_category(value, value_min, value_max, num_colors);
  setColor(color_scale[color_index]);
}

/*
void TM_LED_KY_016_Class::fadeIn_fadeOut()
{
  int brightness_step = 5;

  for (int brightness = 0; brightness <= 255; brightness += brightness_step)
  {
    // set the brightness on LEDC channel 0
    analogWrite(pin_red, brightness);
    delay(30);
  }
  for (int brightness = 255; brightness >= 0; brightness -= brightness_step)
  {
    // set the brightness on LEDC channel 0
    analogWrite(pin_red, brightness);
    delay(30);
  }
}
*/