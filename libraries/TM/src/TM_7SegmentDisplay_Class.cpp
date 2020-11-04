/*
Class for accessing 4 x 7 segment clock display
*/

#include <Arduino.h>

#include "TM_Device_Class.h"
#include "TM_7SegmentDisplay_Class.h"
#include "TM_Helper.h"

#include <TM1637Display.h>

TM_7SegmentDisplay_Class::TM_7SegmentDisplay_Class(const uint8_t pin_clk, const uint8_t pin_dio, const bool v) : TM_Display_Device_Class(v), myDisplay(pin_clk, pin_dio)
{
  myDisplay.clear();
  myDisplay.setBrightness(0x0f);
}

void TM_7SegmentDisplay_Class::setBrightness(uint8_t brightness)
{
  // 0 -> min, 7 -> max
  myDisplay.setBrightness(brightness);
}

void TM_7SegmentDisplay_Class::displayValue(uint16_t value)
{
  if (value > 9999)
    value = 9999;
  myDisplay.showNumberDec(value, false);
}

void TM_7SegmentDisplay_Class::displayValueAndSetBrightness(uint16_t value)
{
  uint8_t brightnessLevel = tm_helper_value_to_category(value, value_min, value_max, num_brightness_levels);

  setBrightness(brightnessLevel);
  displayValue(value);
}
