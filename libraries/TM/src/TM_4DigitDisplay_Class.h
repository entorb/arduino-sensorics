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
  void setBrightness(uint8_t value);
  void displayValue(uint16_t value);

  // display of a float as xx:x using the ":" as decimal separator
  // displaying only one digit -> 12.34 -> 12:3
  // restricted to values v < 100 and v >= 0 
  void displayValue2p1(float value);

  void displayValueAndSetBrightness(uint16_t value);

private:
  TM1637Display myDisplay;
  const uint8_t num_brightness_levels = 7;
  const uint8_t segments_blank[4] = {0x00, 0x00, 0x00, 0x00};
};
#endif
