/*
  TM_InfluxDB.h - Library for Connection to my InfluxDB
*/

#ifndef TM_InfluxDB_h
#define TM_InfluxDB_h

#include <InfluxDbClient.h>

void TM_connect_wifi(char *);
void TM_connect_influxdb();
void TM_influx_send_point(Point);

#endif
