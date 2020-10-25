/*
  TM_BME280.cpp - Library for Connection to Sensor BME280 (Temp, Humidity, Pressure) via I2C
*/

#include <Arduino.h>
#include "TM_BME280.h"

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

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
                     //Adafruit_BME280 bme(BME_CS); // hardware SPI
                     //Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

float TM_BME280_data[3];

void TM_BME280_init()
{
  Serial.println(F("BME280 test"));

  unsigned status;

  // You can also pass in a Wire library object like &Wire2
  status = bme.begin(0x76); //, &Wire2
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    while (1)
      delay(10);
  }
}

float *TM_BME280_read_values(bool print)
{
  TM_BME280_data[0] = bme.readTemperature();
  if (print)
  {
    Serial.print("Temperature = ");
    Serial.print(TM_BME280_data[0]);
    Serial.println(" *C");
  }

  TM_BME280_data[1] = bme.readHumidity();
  if (print)
  {
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
  }
  TM_BME280_data[2] = bme.readPressure();
  if (print)
  {
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.println();
  }
  /*
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
*/
  return (float *)&TM_BME280_data; // return array of floats
}
