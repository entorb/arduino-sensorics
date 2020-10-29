/*
  TM_BME280.h - Library for Connection to Sensor BME280 (Temp, Humidity, Pressure) via I2C
*/

#ifndef TM_BME280_h
#define TM_BME280_h

void TM_BME280_init();
float *TM_BME280_read_values(bool);

#endif
