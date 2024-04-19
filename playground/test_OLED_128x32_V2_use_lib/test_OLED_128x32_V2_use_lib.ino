
//#include <Arduino.h>
#include "TM_OLED_128x32.h"

const char *text = "Mojn5en";

void setup()
{
  TM_OLED_128x32_init();
}

void loop()
{
  TM_OLED_128x32_drawStr(8, 7, text);
  delay(1000);
}
