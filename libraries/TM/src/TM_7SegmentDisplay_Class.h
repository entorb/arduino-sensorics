/*
Class for accessing 4 x 7 segment clock display
*/

#ifndef TM_7SEGMENTDISPLAY_CLASS_H
#define TM_7SEGMENTDISPLAY_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

#include <TM1637Display.h>

class TM_7SegmentDisplay_Class : public TM_Device_Class
{
public:
  // constructor
  TM_7SegmentDisplay_Class(const uint8_t pin_clk, const uint8_t pin_dio, const bool verbose = false);
  // functions
  void test();
  void setBrightness(uint8_t brightness);
  void displayValue(uint16_t value);
  // variables

private:
  uint8_t data[4] = {0xff, 0xff, 0xff, 0xff};
  TM1637Display myDisplay;
};
#endif
