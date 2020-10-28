#include <Arduino.h>
#include "TM_Test_Class.h"

TM_Test_Class myObject;

void setup()
{
    myObject.set_a(1);
    myObject.set_b();
}

void loop()
{
    int ab = myObject.get_a_plus_b();
}