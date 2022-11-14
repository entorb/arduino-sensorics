/*
Class for reading BME280 Temperature, Humidity and Pressure Sensor
*/

#ifndef TM_BME280_CLASS_H
#define TM_BME280_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

#include <Adafruit_BME280.h>

class TM_BME280_Class : public TM_Sensor_Device_Class
{
public:
  // constructor
  TM_BME280_Class(const bool verbose = false);
  // variables
  // functions
  void init();
  float *read_values();

private:
  unsigned status;
  float data[3];
  Adafruit_BME280 bme; // I2C
                       //Adafruit_BME280 bme(BME_CS); // hardware SPI
                       //Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
};
#endif
