/*
  TM_InfluxDB.cpp - Library for Connection to my WiFi
  based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino
*/

#include "Arduino.h"
#include "TM_InfluxDB.h"

//WiFi
#include <WiFi.h>
// #if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti my_wifiMulti;
// #elif defined(ESP8266)
// #include <ESP8266WiFiMulti.h>
// ESP8266WiFiMulti my_wifiMulti;
// #endif

#include "esp_wifi.h" // for esp_wifi_set_ps (WIFI_PS_MODEM); = power saving

#include <InfluxDbClient.h>
// #include <InfluxDbCloud.h>

#include "TM_WiFi_secret.h"
// defines INFLUXDB_URL, INFLUXDB_DB_NAME
#include "TM_InfluxDB_secret.h"
// defines INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD

// TimeZone for Time Sync Central Europe: "CET-1CEST,M3.5.0,M10.5.0/3"
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

// InfluxDB client instance for InfluxDB 1
InfluxDBClient my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME);

void TM_connect_wifi(char *devicename)
{
  // esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
  // TODO: add some timeout / retry mechanism
  Serial.println("Connecting to WiFi");
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
    Serial.print(".");
    delay(500);
    i++;
  }
  Serial.println();
  // Sync Time
  timeSync(TZ_INFO, "de.pool.ntp.org");
  esp_wifi_set_ps(WIFI_PS_MODEM);
}

void TM_connect_influxdb()
{
  // Set Influx Connection Settings
  Serial.println("Setting InfluxDB 1.X authentication params");
  my_InfluxClient.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  // Test InfluxDB connection
  if (my_InfluxClient.validateConnection())
  {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(my_InfluxClient.getServerUrl());
  }
  else
  {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(my_InfluxClient.getLastErrorMessage());
  }
}

void TM_influx_send_point(Point sensor)
{
  Serial.print("Sending: ");
  Serial.println(sensor.toLineProtocol());
  // If no Wifi signal, try to reconnect it
  if ((WiFi.RSSI() == 0) && (my_wifiMulti.run() != WL_CONNECTED))
    Serial.println("Wifi connection lost");
  // Write point
  if (!my_InfluxClient.writePoint(sensor))
  {
    Serial.print("InfluxDB write failed: ");
    Serial.println(my_InfluxClient.getLastErrorMessage());
  }
}
