/*
Class for accessing 4 x 7 segment clock display
*/

#include <Arduino.h>

#include "TM_Device_Class.h"
#include "TM_7SegmentDisplay_Class.h"

#include <TM1637Display.h>

// Module connection pins (Digital Pins)
// #define CLK 26
// #define DIO 25

TM_7SegmentDisplay_Class::TM_7SegmentDisplay_Class(const uint8_t pin_clk, const uint8_t pin_dio, const bool v) : TM_Device_Class(v), myDisplay(pin_clk, pin_dio)
{
  myDisplay.clear();
  myDisplay.setBrightness(0x0f);
}

void TM_7SegmentDisplay_Class::test()
{
  myDisplay.clear();
  myDisplay.setBrightness(0x0f);

  // Selectively set different digits
  // data[0] = myDisplay.encodeDigit(0);
  // data[1] = myDisplay.encodeDigit(1);
  // data[2] = myDisplay.encodeDigit(2);
  // data[3] = myDisplay.encodeDigit(3);
  // myDisplay.setSegments(data);
  // delay(1000);

  // myDisplay.showNumberDec(301, false); // Expect: _301
  // myDisplay.showNumberDec(301, true); // Expect: 0301

  myDisplay.showNumberDec(1234, false);

  for (int k = 0; k < 7; k++)
  {
    Serial.println(k);
    myDisplay.setBrightness(k);
    myDisplay.setSegments(data);
    delay(1000);
  }
}

void TM_7SegmentDisplay_Class::setBrightness(uint8_t brightness)
{
  // 0 -> off, 7 -> max
  myDisplay.setBrightness(brightness);
}

void TM_7SegmentDisplay_Class::displayValue(uint16_t value)
{
  if (value > 9999)
    value = 9999;
  myDisplay.showNumberDec(value, false);
}

//TODO: calc brightness based on value, min, max