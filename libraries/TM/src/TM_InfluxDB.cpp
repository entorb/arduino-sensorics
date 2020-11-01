/*
  TM_InfluxDB.cpp - Library for Connection to my WiFi
  based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino
*/

// InfluxDB
#include "TM_Device_Class.h"
#include "TM_InfluxDB.h"
#include "TM_InfluxDB_secret.h"

#include "Arduino.h"

#include <InfluxDbClient.h>

//WiFi
#include <WiFi.h>
// #if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti my_wifiMulti;
// #elif defined(ESP8266)
// #include <ESP8266WiFiMulti.h>
// ESP8266WiFiMulti my_wifiMulti;
// #endif
#include "TM_WiFi_secret.h"
#include "esp_wifi.h" // for esp_wifi_set_ps (WIFI_PS_MODEM); = power saving

// TODO: how to move this as private variabled into the class???
// InfluxDB client instance for InfluxDB 1
InfluxDBClient my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME);

TM_Influx_Class::TM_Influx_Class() : TM_Device_Class()
{
}

void TM_Influx_Class::connect_wifi(const char *devicename)
{
  // esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
  // TODO: add some timeout / retry mechanism
  if (verbose == true)
  {
    Serial.println("Connecting to WiFi");
  }
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  // delay(1000);
  WiFi.setHostname(devicename);
  WiFi.mode(WIFI_STA);
  my_wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  int i = 0;
  while (my_wifiMulti.run() != WL_CONNECTED)
  {
    if (i == 15)
    {
      WiFi.reconnect();
      i = 0;
    }
    if (verbose == true)
    {
      Serial.print(".");
    }
    delay(500);
    i++;
  }
  if (verbose == true)
  {
    Serial.println();
  }
  esp_wifi_set_ps(WIFI_PS_MODEM);
}

void TM_Influx_Class::connect_influxdb()
{
  // Set Influx Connection Settings
  if (verbose == true)
  {
    Serial.println("Setting InfluxDB 1.X authentication params");
  }
  my_InfluxClient.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  // Test InfluxDB connection
  if (my_InfluxClient.validateConnection())
  {
    if (verbose == true)
    {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(my_InfluxClient.getServerUrl());
    }
  }
  else
  {
    if (verbose == true)
    {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(my_InfluxClient.getLastErrorMessage());
    }
  }
}

void TM_Influx_Class::send_point(Point sensor)
{
  if (verbose == true)
  {
    Serial.print("Sending: ");
    Serial.println(sensor.toLineProtocol());
  }
  // If no Wifi signal, try  reconnecting
  if ((WiFi.RSSI() == 0) && (my_wifiMulti.run() != WL_CONNECTED))
    if (verbose == true)
    {
      Serial.println("Wifi connection lost");
    }
  // Write point
  if (!my_InfluxClient.writePoint(sensor))
  {
    if (verbose == true)
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