/*
Class for accessing 4 x 7 segment clock display
*/

#ifndef TM_DIGITDISPLAY_CLASS_H
#define TM_DIGITDISPLAY_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

#include <TM1637Display.h>

class TM_4DigitDisplay_Class : public TM_Display_Device_Class
{
public:
  // constructor
  TM_4DigitDisplay_Class(const uint8_t pin_clk, const uint8_t pin_dio, const bool verbose = false);
  // functions
  void ensure_wake();
  void ensure_sleep();
  void displayValue(uint16_t value);
  void displayValueAndSetBrightness(uint16_t value);

private:
  TM1637Display myDisplay;
  const uint8_t num_brightness_levels = 7;
  const uint8_t segments_blank[4] = {0x00, 0x00, 0x00, 0x00};
};
#endif
