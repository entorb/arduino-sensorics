/*
Helper functions
*/

#include "Arduino.h"
#include "TM_Helper.h"

uint8_t tm_helper_value_to_category(const float value, const float value_min, const float value_max, const uint8_t number_of_cat)
// converts a value with respect to min and max to a caterory, for example set number
{
    uint8_t cat_number = 0;
    if (value <= value_min)
        cat_number = 0; // first
    else if (value >= value_max)
        cat_number = number_of_cat - 1; // -> last
    else
    {
        // convert value to category number
        const float value_rel = value - value_min;
        const float range_rel = value_max - value_min;
        cat_number = number_of_cat * (value_rel / range_rel);
    }
    return cat_number;
}