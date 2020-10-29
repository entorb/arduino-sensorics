/*
  TM_InfluxDB.h - Library for Connection to my InfluxDB
*/

#ifndef TM_InfluxDB_H
#define TM_InfluxDB_H

#include <InfluxDbClient.h>

class TM_Influx_Class
{
public:
  // constructor
  TM_Influx_Class();
  // variables
  // functions
  void connect_wifi(char *);
  void connect_influxdb();
  void send_point(Point);

private:
  // InfluxDBClient my_InfluxClient;
};
#endif
