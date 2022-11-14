
#include "TM_BME280.h"

//float TM_BME280_data[3];

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ; // time to get serial running

    TM_BME280_init();
}

void loop()
{
    float *TM_BME280_data = TM_BME280_read_values(true);

    // 0 = T, 1 = Humidity, 2 = Pressure
    delay(1000);
}
