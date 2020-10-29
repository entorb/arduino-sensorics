/*
  TM_MH-Z19_Class.cpp - Library for reading a MH-Z19 CO2 sensor
  Based on MHZ19 BasicExample
*/

#include "TM_Sensor_Class.h"
#include "TM_MH-Z19_Class.h"
#include <Arduino.h>
#include "MHZ19.h"

#define RX_PIN 16           // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 17           // Tx pin which the MHZ19 Rx pin is attached to
#define MHZ19_BAUDRATE 9600 // Device to MH-Z19 Serial baudrate (should not be changed)

// TODO: move into class, but this led to reboots of the Arduino, so research needed
HardwareSerial mySerial_Class(1); // (ESP32 Example) create device to MH-Z19 serial

TM_MH_Z19_Class::TM_MH_Z19_Class() : TM_Sensor_Class()
{
}

void TM_MH_Z19_Class::init()
{
  if (verbose)
  {
    Serial.println(F("MH-Z19 init"));
  }
  //  HardwareSerial mySerial(1);
  mySerial_Class.begin(MHZ19_BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN); // (ESP32 Example) device to MH-Z19 serial start
  myMHZ19.begin(mySerial_Class);                                    // *Serial(Stream) reference must be passed to library begin().

  // calibration
  /*   
      myMHZ19.setRange(2000);
      myMHZ19.calibrateZero();
      myMHZ19.setSpan(2000);
  */
  myMHZ19.autoCalibration(true);
}

int TM_MH_Z19_Class::read_values()
{
  int CO2 = myMHZ19.getCO2();
  //  int8_t Temp= myMHZ19.getTemperature();
  if (verbose)
  {
    Serial.print("CO2 = ");
    Serial.print(CO2);
    Serial.println(" ppm");
  }
  return CO2;
}