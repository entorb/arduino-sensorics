/*
  TM_InfluxDB.h - Library for Connection to my InfluxDB
*/

#ifndef TM_INFLUXDB_H
#define TM_INFLUXDB_H

#include "TM_Device_Class.h"
#include "TM_InfluxDB_secret.h"

#include <InfluxDbClient.h>
#include <WiFiMulti.h>

class TM_Influx_Class : public TM_Device_Class
{
private:
  // InfluxDBClient my_InfluxClient;
  WiFiMulti my_wifiMulti;

public:
  // constructor
  TM_Influx_Class();
  // TM_Influx_Class() : my_InfluxClient(INFLUXDB_URL, INFLUXDB_DB_NAME);
  // variables
  // functions
  void connect_wifi(const char *);
  void connect_influxdb();
  void send_point(Point);
  void sync_time();
};
#endif
