/*
Class for reading BME280 Temperature, Humidity and Pressure Sensor


*/

// Based on:
/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_BME280_Class.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
/*
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
*/

TM_BME280_Class::TM_BME280_Class(const bool this_verbose) : TM_Sensor_Device_Class("BME280", this_verbose)
{
}

void TM_BME280_Class::init()
{
  TM_Sensor_Device_Class::init();
  // You can also pass in a Wire library object like &Wire2
  status = bme.begin(0x76); //, &Wire2
  if (!status)
  {
    if (verbose)
    {
      TM_Device_Class::printDeviceName();
      Serial.println("Could not find a valid sensor, check wiring, address, sensor ID!");
      TM_Device_Class::printDeviceName();
      Serial.print("SensorID was: 0x");
      Serial.println(bme.sensorID(), 16);
    }
    while (1)
      delay(10);
  }
}

float *TM_BME280_Class::read_values()
{
  data[0] = bme.readTemperature();
  data[1] = bme.readHumidity();
  data[2] = bme.readPressure() / 100.0F;
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.print("Temperature = ");
    Serial.print(data[0]);
    Serial.println(" C");
    TM_Device_Class::printDeviceName();
    Serial.print("Humidity = ");
    Serial.print(data[1]);
    Serial.println(" %");
    TM_Device_Class::printDeviceName();
    Serial.print("Pressure = ");
    Serial.print(data[3]);
    Serial.println(" hPa");
    /*                                              \
  Serial.print("Approx. Altitude = ");                  \
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); \
  Serial.println(" m");                                 \
  */
  }
  return (float *)&data; // return array of floats
}
