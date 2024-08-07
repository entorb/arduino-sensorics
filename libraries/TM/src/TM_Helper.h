/*
Helper functions
*/
#ifndef TM_HELPER_H
#define TM_HELPER_H

#include "Arduino.h"

uint8_t tm_helper_value_to_category(const float value, const float value_min, const float value_max, const uint8_t number_of_cat);

#endif
