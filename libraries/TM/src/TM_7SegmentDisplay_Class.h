/*
Class for accessing 4 x 7 segment clock display
*/

#ifndef TM_7SEGMENTDISPLAY_CLASS_H
#define TM_7SEGMENTDISPLAY_CLASS_H

#include "Arduino.h"
#include "TM_Device_Class.h"

class TM_7SegmentDisplay_Class : public TM_Device_Class
{
public:
  // constructor
  TM_7SegmentDisplay_Class(const bool verbose = false);
  // functions
  void init();
  // variables

private:
  //
};
#endif
