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
  myDisplay.setBrightness(7, true);
}
void TM_7SegmentDisplay_Class::ensure_wake()
{
  if (sleeping == true)
  {
    TM_Display_Device_Class::ensure_wake();
    myDisplay.setBrightness(7, true);
  }
}
void TM_7SegmentDisplay_Class::ensure_sleep()
{
  if (sleeping == false)
  {
    TM_Display_Device_Class::ensure_sleep();
    myDisplay.setBrightness(7, false); // not working :-(
    myDisplay.setSegments(segments_blank);
  }
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

  myDisplay.setBrightness(brightnessLevel, true);
  displayValue(value);
}
