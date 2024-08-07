/*
  Class for connection to WiFi
*/

#ifndef TM_WIFI_H
#define TM_WIFI_H

#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_WiFi_secret.h"

class TM_WiFi_Class : public TM_Device_Class
{
  // private:

public:
  // constructor
  TM_WiFi_Class(const bool verbose = false);
  // variables
  // functions
  void connect();
};
#endif
