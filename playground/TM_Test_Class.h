/*
TM_Test_Class.h - experimenting with classes and objects in C++ / Arduino
*/

#ifndef TM_Test_Class_H
#define TM_Test_Class_H

#include <Arduino.h>

class TM_Test_Class
{
public:
    // Variables
    int a;

    // Set Functions
    void set_a(int value = 2); // default to 2
    void set_b(int value = 3); // default to 3

    // Get Functions
    int get_a_plus_b();

    // Utility Functions

private:
    // Variables
    int b;
    // Internal Functions
};
#endif