/*
  TM_InfluxDB.h - Library for Connection to my InfluxDB
*/

#ifndef TM_INFLUXDB_H
#define TM_INFLUXDB_H

#include "TM_Device_Class.h"

#include <InfluxDbClient.h>

class TM_Influx_Class : public TM_Device_Class
{
public:
  // constructor
  TM_Influx_Class();
  // variables
  // functions
  void connect_wifi(const char *);
  void connect_influxdb();
  void send_point(Point);
  void sync_time();

private:
  // InfluxDBClient my_InfluxClient;
};
#endif
