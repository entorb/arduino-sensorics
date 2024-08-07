/*
  Class for connection to WiFi
*/

#include "Arduino.h"
#include "TM_Device_Class.h"

// WiFi
#include <WiFi.h>
#include "TM_WiFi_Class.h"
#include "TM_WiFi_secret.h"
#include "esp_wifi.h" // for esp_wifi_set_ps (WIFI_PS_MODEM); = power saving

TM_WiFi_Class::TM_WiFi_Class(const bool this_verbose) : TM_Device_Class("WiFi", this_verbose) {}

void TM_WiFi_Class::connect()
{
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.println("Connecting to WiFi");
  }

  // Old version
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
  // WiFi.setHostname(devicename);
  // WiFi.mode(WIFI_STA);
  // WiFi.setHostname(devicename);
  // my_wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  // while (my_wifiMulti.run() != WL_CONNECTED)

  // New Version
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE); // required to set hostname properly
  WiFi.setHostname(devicename);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    if (i == 15)
    {
      WiFi.reconnect();
      i = 0;
    }
    if (verbose)
      Serial.print(".");
    delay(500);
    i++;
  }
  if (verbose)
    Serial.println();

  // enable Power Saving Modem -> only WiFi keep alive
  // esp_wifi_set_ps(WIFI_PS_MODEM); // ESP32 1.0.4
  // esp_wifi_set_ps(WIFI_PS_MIN_MODEM); // ESP32 2.0.0, see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html
  esp_wifi_set_ps(WIFI_PS_MAX_MODEM); // ESP32 2.0.0, see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html
}
