/*
  TM_Device_Class.h - My Sensor interface
*/

#ifndef TM_DEVICE_CLASS_H
#define TM_DEVICE_CLASS_H

class TM_Device_Class
{
public:
  // constructor
  TM_Device_Class();
  // functions
  void init();
  void setVerbose(bool);
  // variables
  bool verbose;
  // Idea:
  // char devicename[8];

private:
};
#endif
