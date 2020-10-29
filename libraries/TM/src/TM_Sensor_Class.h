/*
  TM_Sensor_Class.h - My Sensor interface
*/

#ifndef TM_Sensor_Class_H
#define TM_Sensor_Class_H

class TM_Sensor_Class
{
public:
  // constructor
  TM_Sensor_Class();
  // functions
  void init();
  void setVerbose(bool);
  // variables
  bool verbose;

private:
};
#endif
