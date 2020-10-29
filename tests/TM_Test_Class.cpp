/*
TM_Test_Class.cpp - experimenting with classes and objects in C++ / Arduino
*/
#include "TM_Test_Class.h"

void TM_Test_Class::set_a(int value)
{
    a = value;
}

void TM_Test_Class::set_b(int value)
{
    b = value;
}

int TM_Test_Class::get_a_plus_b()
{
    return (a + b);
}