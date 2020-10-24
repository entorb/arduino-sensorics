/*
  TM_InfluxDB.cpp - Library for Connection to my WiFi
  based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino
*/

#include "Arduino.h"
#include "TM_InfluxDB.h"

#include <WiFiMulti.h>
WiFiMulti TM_wifiMulti;

#include <InfluxDbClient.h>
// #include <InfluxDbCloud.h>

#include "TM_WiFi_secret.h"
// defines INFLUXDB_URL, INFLUXDB_DB_NAME
#include "TM_InfluxDB_secret.h"
// defines INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD

// TimeZone for Time Sync Central Europe: "CET-1CEST,M3.5.0,M10.5.0/3"
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

// InfluxDB client instance for InfluxDB 1
InfluxDBClient TM_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME);

void TM_connect_wifi(char *devicename)
{
  Serial.println("Connecting to WiFi");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  WiFi.setHostname(devicename);
  WiFi.mode(WIFI_STA);
  TM_wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (TM_wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  // Sync Time
  timeSync(TZ_INFO, "de.pool.ntp.org");
}
void TM_connect_influxdb()
{
  // Set Influx Connection Settings
  Serial.println("Setting InfluxDB 1.X authentication params");
  TM_InfluxClient.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  // Test InfluxDB connection
  if (TM_InfluxClient.validateConnection())
  {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(TM_InfluxClient.getServerUrl());
  }
  else
  {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(TM_InfluxClient.getLastErrorMessage());
  }
}
void TM_influx_send_point(Point sensor)
{
  Serial.print("Sending: ");
  Serial.println(sensor.toLineProtocol());
  // If no Wifi signal, try to reconnect it
  if ((WiFi.RSSI() == 0) && (TM_wifiMulti.run() != WL_CONNECTED))
    Serial.println("Wifi connection lost");
  // Write point
  if (!TM_InfluxClient.writePoint(sensor))
  {
    Serial.print("InfluxDB write failed: ");
    Serial.println(TM_InfluxClient.getLastErrorMessage());
  }
}
