/*
  Class for connection to MQTT
*/

#ifndef TM_WIFI_H
#define TM_WIFI_H

#include "Arduino.h"
#include "TM_Device_Class.h"

#include "TM_MQTT_secret.h"
#include <PubSubClient.h>

class TM_MQTT_Class : public TM_Device_Class
{
  // private:

public:
  // constructor
  TM_MQTT_Class(const bool verbose = false);
  // variables
  // functions
  void connect();
};
#endif
