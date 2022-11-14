/*
Class for accessing 4 x 7 segment clock display
*/

#include <Arduino.h>

#include "TM_Device_Class.h"
#include "TM_4DigitDisplay_Class.h"
#include "TM_Helper.h"

#include <TM1637Display.h>

TM_4DigitDisplay_Class::TM_4DigitDisplay_Class(const uint8_t pin_clk, const uint8_t pin_dio, const bool this_verbose) : TM_Display_Device_Class("4Digit", this_verbose), myDisplay(pin_clk, pin_dio)
{
  myDisplay.clear();
  myDisplay.setBrightness(7, true);
}
void TM_4DigitDisplay_Class::ensure_wake()
{
  if (sleeping == true)
  {
    TM_Display_Device_Class::ensure_wake();
    myDisplay.setBrightness(7, true);
  }
}
void TM_4DigitDisplay_Class::ensure_sleep()
{
  if (sleeping == false)
  {
    TM_Display_Device_Class::ensure_sleep();
    myDisplay.setBrightness(7, false); // not working :-(
    myDisplay.setSegments(segments_blank);
  }
}

void TM_4DigitDisplay_Class::setBrightness(uint8_t value)
{
  if (value > 7)
    value = 7;
  myDisplay.setBrightness(value, true);
}

void TM_4DigitDisplay_Class::displayValue(uint16_t value)
{
  if (value > 9999)
    value = 9999;
  myDisplay.showNumberDec(value, false);
}

void TM_4DigitDisplay_Class::displayValue2p1(float value)
{
  if (value > 100)
    value = 99.9;
  uint16_t i = value * 10;
  myDisplay.clear();
  myDisplay.showNumberDecEx(i, 0b01000000, false, 3, 0);
}

void TM_4DigitDisplay_Class::displayTime(uint8_t hour, uint8_t min)
//TODO: 0:12 -> :12 as leading zeros are lost due to integer
{
  if (hour > 23)
    hour = 12;
  if (min > 60)
    min = 0;
  uint16_t i = hour * 100 + min;
  myDisplay.clear();
  myDisplay.showNumberDecEx(i, 0b01000000, false);
}

void TM_4DigitDisplay_Class::displayValueAndSetBrightness(uint16_t value)
{
  uint8_t brightnessLevel = tm_helper_value_to_category(value, value_min, value_max, num_brightness_levels);

  myDisplay.setBrightness(brightnessLevel, true);
  displayValue(value);
}
