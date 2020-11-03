/*
  TM_LED_Ring_Class.h - Library for powering WS2812 LED Ring
*/
#ifndef TM_LED_KY_016_H
#define TM_LED_KY_016_H

#include "TM_Device_Class.h"

#include "Arduino.h"

class TM_LED_KY_016_Class : public TM_Device_Class
{
public:
  // constructor

  // functions
  void ledcAnalogWrite(uint8_t, uint32_t, uint32_t);
  void fadeIn_fadeOut();
  // variables

private:
  // variables
  int brightness = 0; // how bright the LED is
  int fadeAmount = 5; // how many points to fade the LED by
                      // currently as many colors as pixels, but this could be changed
};
#endif
