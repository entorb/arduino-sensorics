// based on https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino/blob/master/examples/BasicWrite/BasicWrite.ino

#include "TM_InfluxDB.h"

#define MEASUREMENT "ArduinoTestMeasurement"
#define DEVICENAME "T-ESP32-1"
#define TAG_ROOM "Arbeitszimmer"

// Data point
Point sensor(MEASUREMENT);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // time to get serial running
  // Set constant tags - only once
  sensor.addTag("device", DEVICENAME);
  sensor.addTag("room", TAG_ROOM);

  TM_connect_wifi(DEVICENAME);
  TM_connect_influxdb();
  Serial.println("Setup Done");
}

void loop()
{
  sensor.clearFields();
  sensor.addField("temperature", random(20, 30));
  sensor.addField("humidity", random(0, 100));

  TM_influx_send_point(sensor);

  Serial.println("Loop Done");
  delay(1000);
}
