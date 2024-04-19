/*
Class for powering 3 color RGB LED KY-016
*/

#ifndef TM_LED_KY_016_H
#define TM_LED_KY_016_H

#include "Arduino.h"
#include "TM_Device_Class.h"

class TM_LED_KY_016_Class : public TM_Display_Device_Class
{
public:
  // constructor
  TM_LED_KY_016_Class(const uint8_t pin_red, const uint8_t pin_green, const uint8_t pin_blue, const bool verbose = false);
  // functions
  // void setValueRange(const float, const float);
  void setColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t brightness = 255);
  void setColor(const uint32_t rgb, const uint8_t brightness = 255);
  void displayValue(const float);
  // void fadeIn_fadeOut();
  // variables
  const uint32_t color_scale[3] = {
      0x00ff00, // green
      0x0000ff, // blue
      //0xff7f00, // yellow
      // 0xffA500, // orange
      0xff0000 // red
  };

private:
  // variables
  uint8_t pin_red;
  uint8_t pin_green;
  uint8_t pin_blue;
};
#endif
