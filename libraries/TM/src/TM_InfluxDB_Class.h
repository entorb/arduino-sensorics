/*
  TM_InfluxDB_Class.h - Library for Connection to my InfluxDB
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
  WiFiMulti my_wifiMulti;

public:
  // InfluxDBClient my_InfluxClient;
  // constructor
  TM_Influx_Class();
  // variables
  // functions
  void connect_wifi(const char *);
  void connect_influxdb();
  void send_point(Point);
  void sync_time();
};
#endif
