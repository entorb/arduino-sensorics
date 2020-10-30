#include <Arduino.h>
#include "TM_BME280_Class.h"

auto my_bme280 = TM_BME280_Class(true); // ??? verbose = true would be nicer

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ; // time to get serial running

    my_bme280.init();
}

void loop()
{
    float *bme_data = my_bme280.read_values();

    // 0 = T, 1 = Humidity, 2 = Pressure
    delay(1000);
}