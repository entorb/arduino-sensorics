/*
  TM_MH-Z19_Class.h - Library for reading a MH-Z19 CO2 sensor
*/

#ifndef TM_MH_Z19_CLASS_H
#define TM_MH_Z19_CLASS_H

#include "TM_Device_Class.h"

#include <Arduino.h>
#include "MHZ19.h"
#define RX_PIN 16           // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 17           // Tx pin which the MHZ19 Rx pin is attached to
#define MHZ19_BAUDRATE 9600 // Device to MH-Z19 Serial baudrate (should not be changed)

class TM_MH_Z19_Class : public TM_Device_Class
{
public:
  // constructor
  TM_MH_Z19_Class();
  // functions
  void init();
  int read_values();
  // variables
  // TODO: Tut nicht :-(
  // HardwareSerial mySerial_Class(1); // (ESP32 Example) create device to MH-Z19 serial

private:
  MHZ19 myMHZ19;
};
#endif
