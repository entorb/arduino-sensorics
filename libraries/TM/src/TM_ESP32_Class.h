/*
Class for EPS32 Microcontroller 
*/

#ifndef TM_ESP32_CLASS_H
#define TM_ESP32_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

// see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/log.html
#define LOG_LOCAL_LEVEL ESP_LOG_ERROR
// #include "esp_log.h"
// esp_log_level_set("*", ESP_LOG_ERROR);

class TM_ESP32_Class : public TM_Device_Class
{
public:
  // constructor
  TM_ESP32_Class(const bool verbose = false);
  // variables
  // functions
  void restart();
  void underclocking();
  void normalclocking();
  void printSpeed();

private:
};
#endif
