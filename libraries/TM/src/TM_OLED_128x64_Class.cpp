/*
  TM_OLED_128x64_Class.cpp - Library for Connection to 128x64 OLED Display
*/

#include "TM_Device_Class.h"
#include "TM_OLED_Class.h"
#include "TM_OLED_128x64_Class.h"

// #include <Arduino.h>
#include "U8g2lib.h"
// #ifdef U8X8_HAVE_HW_SPI
// #include <SPI.h>
// #endif
// #ifdef U8X8_HAVE_HW_I2C
// #include <Wire.h>
// #endif

// Initialisierungsliste
TM_OLED_128x64_Class ::TM_OLED_128x64_Class() : TM_OLED_Class(), my_u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
{
  px_x = 128;
  px_y = 64;
  barchart_data[px_x] = {0}; // initialize with all with 0
}
