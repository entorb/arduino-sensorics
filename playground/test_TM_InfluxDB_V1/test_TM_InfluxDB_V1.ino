// based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino

#include <WiFiMulti.h>
WiFiMulti wifiMulti;

#include <InfluxDbClient.h>
// #include <InfluxDbCloud.h>

#include "TM_WiFi_secret.h"
// defines INFLUXDB_URL, INFLUXDB_DB_NAME
#include "TM_InfluxDB_secret.h"
// defines INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD

// TimeZone for Time Sync Central Europe: "CET-1CEST,M3.5.0,M10.5.0/3"
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

#define MEASUREMENT "ArduinoTestMeasurement"
#define DEVICENAME "T-ESP32-1"
#define TAG_ROOM "Arbeitszimmer"

// InfluxDB client instance for InfluxDB 1
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

// Data point
Point sensor(MEASUREMENT);

void setup()
{
  Serial.begin(115200);
  // Set constant tags - only once
  sensor.addTag("device", DEVICENAME);
  sensor.addTag("room", TAG_ROOM);

  // -------------------------
  // TODO: connect_wifi()
  // -------------------------
  Serial.println("Connecting to WiFi");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  WiFi.setHostname(DEVICENAME);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  // Sync Time
  timeSync(TZ_INFO, "de.pool.ntp.org");

  // -------------------------
  // TODO: connect_influxdb()
  // -------------------------
  // Set Influx Connection Settings
  Serial.println("Setting InfluxDB 1.X authentication params");
  client.setConnectionParamsV1(INFLUXDB_URL, INFLUXDB_DB_NAME, INFLUXDB_USER, INFLUXDB_PASSWORD);
  // Test InfluxDB connection
  if (client.validateConnection())
  {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  }
  else
  {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop()
{
  sensor.clearFields();
  sensor.addField("temperature", random(20, 30));
  sensor.addField("humidity", random(0, 100));

  // -------------------------
  // TODO: influx_send_point(sensor)
  // -------------------------
  Serial.print("Sending: ");
  Serial.println(sensor.toLineProtocol());
  // If no Wifi signal, try to reconnect it
  if ((WiFi.RSSI() == 0) && (wifiMulti.run() != WL_CONNECTED))
    Serial.println("Wifi connection lost");
  // Write point
  if (!client.writePoint(sensor))
  {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  delay(1000);
}
