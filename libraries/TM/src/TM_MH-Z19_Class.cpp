/*
  TM_MH-Z19_Class.cpp - Library for reading a MH-Z19 CO2 sensor
  Based on MHZ19 BasicExample
*/

#include "TM_Device_Class.h"
#include "TM_MH-Z19_Class.h"

#include <Arduino.h>
#include "MHZ19.h"
#define RX_PIN 16           // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 17           // Tx pin which the MHZ19 Rx pin is attached to
#define MHZ19_BAUDRATE 9600 // Device to MH-Z19 Serial baudrate (should not be changed)

// Initialisierungsliste
TM_MH_Z19_Class::TM_MH_Z19_Class() : TM_Device_Class(), mySerial(1)
{
  mySerial.begin(MHZ19_BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN); // (ESP32 Example) device to MH-Z19 serial start
  myMHZ19.begin(mySerial);                                    // *Serial(Stream) reference must be passed to library begin().
}

void TM_MH_Z19_Class::init()
{
  myMHZ19.autoCalibration(true);

  if (verbose == true)
  {
    Serial.println(F("MH-Z19 init"));
  }

  // calibration
  /*   
      myMHZ19.setRange(2000);
      myMHZ19.calibrateZero();
      myMHZ19.setSpan(2000);
  */
}

int TM_MH_Z19_Class::read_values()
{
  int CO2 = myMHZ19.getCO2();
  //  int8_t Temp= myMHZ19.getTemperature();

  if (verbose == true)
  {
    Serial.print("CO2 = ");
    Serial.print(CO2);
    Serial.println(" ppm");
  }
  return CO2;
}