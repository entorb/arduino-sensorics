/*
  Class for connection to MQTT
*/

#include "Arduino.h"
#include "TM_Device_Class.h"

// MQTT
#include <WiFi.h>
#include "TM_MQTT_Class.h"
#include "TM_MQTT_secret.h"

TM_MQTT_Class::TM_MQTT_Class(const bool this_verbose) : TM_Device_Class("WiFi", this_verbose) {}

void TM_MQTT_Class::connect()
{
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.println("Connecting to WiFi");
  }

  // TODO!!!
}
