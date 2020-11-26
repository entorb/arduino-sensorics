/*
Class for powering 3 color RGB LED KY-016
*/

/*
based on "RGBLed.h"
#include "RGBLed.h"
*/

#include "Arduino.h"
#include <analogWrite.h>

#include "TM_Device_Class.h"
#include "TM_LED_KY_016_Class.h"
#include "TM_Helper.h"

TM_LED_KY_016_Class::TM_LED_KY_016_Class(const uint8_t this_pin_red, const uint8_t this_pin_green, const uint8_t this_pin_blue, const bool this_verbose) : TM_Display_Device_Class("KY-016", this_verbose)
{
  pin_red = this_pin_red;
  pin_green = this_pin_green;
  pin_blue = this_pin_blue;

  pinMode(pin_red, OUTPUT);
  pinMode(pin_green, OUTPUT);
  pinMode(pin_green, OUTPUT);

  digitalWrite(pin_red, LOW);
  digitalWrite(pin_green, LOW);
  digitalWrite(pin_blue, LOW);
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
  analogWrite(pin_red, (red * brightness / 255));
  analogWrite(pin_green, (green * brightness / 255));
  analogWrite(pin_blue, (blue * brightness / 255));
}

void TM_LED_KY_016_Class::displayValue(const float value)
{
  const uint8_t num_colors = sizeof(color_scale) / sizeof(color_scale[0]);
  const uint8_t color_index = tm_helper_value_to_category(value, value_min, value_max, num_colors);
  // use 64 as min brightness
  uint8_t brightness_min = 64;
  uint8_t calc_brightness = brightness_min + tm_helper_value_to_category(value, value_min, value_max, 255 - brightness_min);

  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.print("color_index=");
    Serial.println(color_index);
  }
  setColor(color_scale[color_index], calc_brightness);
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