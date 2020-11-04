/*
Class for accessing 4 x 7 segment clock display
*/

#ifndef TM_7SEGMENTDISPLAY_CLASS_H
#define TM_7SEGMENTDISPLAY_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

#include <TM1637Display.h>

class TM_7SegmentDisplay_Class : public TM_Display_Device_Class
{
public:
  // constructor
  TM_7SegmentDisplay_Class(const uint8_t pin_clk, const uint8_t pin_dio, const bool verbose = false);
  // functions
  void setBrightness(uint8_t brightness);
  void displayValue(uint16_t value);
  void displayValueAndSetBrightness(uint16_t value);

private:
  TM1637Display myDisplay;
  const uint8_t _num_brightness_levels = 7;
};
#endif
