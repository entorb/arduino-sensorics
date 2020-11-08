/*
  Class for connection to WiFi and InfluxDB
  based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino
*/

// InfluxDB
#include "Arduino.h"
#include "TM_Device_Class.h"
#include "TM_InfluxDB_Class.h"
#include "TM_InfluxDB_secret.h"

#include <InfluxDbClient.h>

//WiFi
#include <WiFi.h>
#include "TM_WiFi_secret.h"
#include "esp_wifi.h" // for esp_wifi_set_ps (WIFI_PS_MODEM); = power saving

// TODO: does not like to be moved into Initialisierungsliste:
InfluxDBClient my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME);
TM_Influx_Class::TM_Influx_Class(const bool v) : TM_Device_Class(v) //, my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME)
{
}

void TM_Influx_Class::connect_wifi(const char *devicename)
{
  if (verbose)
    Serial.println("Connecting to WiFi");

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
  esp_wifi_set_ps(WIFI_PS_MODEM);
}

void TM_Influx_Class::connect_influxdb()
{
  // Set Influx Connection Settings
  if (verbose)
    Serial.println("Setting InfluxDB 1.X authentication params");
  my_InfluxClient.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  // Test InfluxDB connection
  if (my_InfluxClient.validateConnection())
  {
    if (verbose)
    {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(my_InfluxClient.getServerUrl());
    }
  }
  else
  {
    if (verbose)
    {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(my_InfluxClient.getLastErrorMessage());
    }
  }
}

void TM_Influx_Class::send_point(Point sensor)
{
  if (verbose)
  {
    Serial.print("Sending: ");
    Serial.println(sensor.toLineProtocol());
  }
  // If no Wifi signal, try  reconnecting
  // if ((WiFi.RSSI() == 0) && (my_wifiMulti.run() != WL_CONNECTED))
  if ((WiFi.RSSI() == 0) && (WiFi.status() != WL_CONNECTED))
  {
    if (verbose)
      Serial.println("Wifi connection lost");
    WiFi.reconnect();
  }

  // Write point
  if (!my_InfluxClient.writePoint(sensor))
  {
    if (verbose)
    {
      Serial.print("InfluxDB write failed: ");
      Serial.println(my_InfluxClient.getLastErrorMessage());
    }
  }
}

void TM_Influx_Class::sync_time()
{
  timeSync("CET-1CEST,M3.5.0,M10.5.0/3", "de.pool.ntp.org");
  // "CET-1CEST,M3.5.0,M10.5.0/3" = Central Europe
}