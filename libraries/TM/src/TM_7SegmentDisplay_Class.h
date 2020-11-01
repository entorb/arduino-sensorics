#ifndef TM_7SEGMENTDISPLAY_CLASS_H
#define TM_7SEGMENTDISPLAY_CLASS_H

#include "TM_Device_Class.h"

#include <Arduino.h>

class TM_7SegmentDisplay_Class : public TM_Device_Class
{
public:
  // constructor
  TM_7SegmentDisplay_Class();
  // functions
  void init();
  // variables

private:
  //
};
#endif
