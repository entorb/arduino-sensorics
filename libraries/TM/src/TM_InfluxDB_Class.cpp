/*
  Class for connection to WiFi and InfluxDB
  based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino
  TODO: remove WIFI from here
*/

// InfluxDB
#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_InfluxDB_Class.h"
#include "TM_InfluxDB_secret.h"

#include <InfluxDbClient.h>

// WiFi
#include <WiFi.h>
#include "TM_WiFi_secret.h"
#include "esp_wifi.h" // for esp_wifi_set_ps (WIFI_PS_MODEM); = power saving

// TODO: pass seconds_min_delay_upload as parameter

// TODO: does not like to be moved into Initialisierungsliste:
InfluxDBClient my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME);
TM_Influx_Class::TM_Influx_Class(const bool this_verbose) : TM_Device_Class("Influx", this_verbose) //, my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME)
{
}

void TM_Influx_Class::connect_wifi(const char *devicename)
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

void TM_Influx_Class::connect_influxdb()
{
  // Set Influx Connection Settings
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.println("Setting InfluxDB 1.X authentication params");
  }
  my_InfluxClient.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  // Test InfluxDB connection
  if (my_InfluxClient.validateConnection())
  {
    if (verbose)
    {
      TM_Device_Class::printDeviceName();
      Serial.print("Connected to: ");
      Serial.println(my_InfluxClient.getServerUrl());
    }
  }
  else
  {
    if (verbose)
    {
      TM_Device_Class::printDeviceName();
      Serial.print("connection failed: ");
      Serial.println(my_InfluxClient.getLastErrorMessage());
    }
  }
}

void TM_Influx_Class::send_point(Point sensor)
{
  uint32_t time = millis();
  // only one upload per minute
  if (time >= time_last_upload + seconds_min_delay_upload * 1000 || time < time_last_upload)
  {
    if (verbose)
    {
      TM_Device_Class::printDeviceName();
      Serial.print("Sending: ");
      Serial.println(sensor.toLineProtocol());
    }
    // If no Wifi signal, try  reconnecting
    // if ((WiFi.RSSI() == 0) && (my_wifiMulti.run() != WL_CONNECTED))
    if ((WiFi.RSSI() == 0) && (WiFi.status() != WL_CONNECTED))
    {
      if (verbose)
      {
        TM_Device_Class::printDeviceName();
        Serial.println("Wifi connection lost");
      }
      WiFi.reconnect();
    }

    // Write point
    if (!my_InfluxClient.writePoint(sensor))
    {
      if (verbose)
      {
        TM_Device_Class::printDeviceName();
        Serial.print("write failed: ");
        Serial.println(my_InfluxClient.getLastErrorMessage());
      }
      num_upload_errors++;
      if (num_upload_errors > 60)
      {
        WiFi.reconnect();
        num_upload_errors = 0;
      }
    }
    else
    {
      time_last_upload = time;
      num_upload_errors = 0;
    }
  }
}

void TM_Influx_Class::sync_time()
{
  if (verbose)
  {
    TM_Device_Class::printDeviceName();
    Serial.println("syncing time");
  }
  timeSync("CET-1CEST,M3.5.0,M10.5.0/3", "de.pool.ntp.org");
  // "CET-1CEST,M3.5.0,M10.5.0/3" = Central Europe
}
