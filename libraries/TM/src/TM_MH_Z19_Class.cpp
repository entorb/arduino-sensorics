/*
Class for reading a MH-Z19 CO2 sensor
Based on MHZ19 BasicExample
*/

#include "TM_Device_Class.h"
#include "TM_MH_Z19_Class.h"

#include <Arduino.h>
#include "MHZ19.h"
// #define RX_PIN 16
// #define TX_PIN 17
#define MHZ19_BAUDRATE 9600 // Device to MH-Z19 Serial baudrate (should not be changed)

// Initialisierungsliste
TM_MH_Z19_Class::TM_MH_Z19_Class(const uint8_t rx, const uint8_t tx, const bool v) : TM_Sensor_Device_Class(v), mySerial(1)
{
  _pin_rx = rx;
  _pin_tx = tx;

  mySerial.begin(MHZ19_BAUDRATE, SERIAL_8N1, _pin_rx, _pin_tx); // (ESP32 Example) device to MH-Z19 serial start
  myMHZ19.begin(mySerial);                                      // *Serial(Stream) reference must be passed to library begin().
  myMHZ19.autoCalibration(true);
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

  if (verbose)
  {
    Serial.print("CO2 = ");
    Serial.print(CO2);
    Serial.println(" ppm");
  }
  return CO2;
}