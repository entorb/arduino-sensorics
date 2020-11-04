/*
Class for accessing 4 x 7 segment clock display
*/

#include <Arduino.h>

#include "TM_Device_Class.h"
#include "TM_7SegmentDisplay_Class.h"

#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO); // TODO: my_display
uint8_t data[4] = {0xff, 0xff, 0xff, 0xff};
uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

TM_7SegmentDisplay_Class::TM_7SegmentDisplay_Class(const bool v) : TM_Device_Class(v)
{
}

void TM_7SegmentDisplay_Class::init()
{
  if (verbose)
  {
    Serial.println(F("TM_7SegmentDisplay_Class init"));
  }

  display.clear();
  display.setBrightness(0x0f);

  // Selectively set different digits
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);

  display.showNumberDec(301, false); // Expect: _301
  display.showNumberDec(301, true);  // Expect: 0301

  for (int k = 0; k < 7; k++)
  {
    display.setBrightness(k);
    display.setSegments(data);
  }
}
