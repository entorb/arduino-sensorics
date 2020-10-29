/*
  TM_BME280_Class.h - Library for Connection to Sensor BME280 (Temp, Humidity, Pressure) via I2C
*/

#ifndef TM_BME280_Class_H
#define TM_BME280_Class_H

#include "TM_Sensor_Class.h"
#include <Adafruit_BME280.h>

class TM_BME280_Class : public TM_Sensor_Class
{
public:
  // constructor
  TM_BME280_Class();
  // variables
  // functions
  void init();
  float *read_values();

private:
  unsigned status;
  float TM_BME280_data[3];
  Adafruit_BME280 bme; // I2C
                       //Adafruit_BME280 bme(BME_CS); // hardware SPI
                       //Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
};
#endif
