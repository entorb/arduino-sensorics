#include <Arduino.h>

#include "TM_InfluxDB.h"
// InfluxDB Setup
#define MEASUREMENT "bme280"
// #1
// #define DEVICENAME "T-ESP32-1"
// #define TAG_ROOM "Schlafzimmer"
// #2
#define DEVICENAME "T-ESP32-2"
#define TAG_ROOM "Kind 1"
// #3
// #define DEVICENAME "T-ESP32-3"
// #define TAG_ROOM "Kind 2"

Point sensor(MEASUREMENT);

#include "TM_BME280_Class.h"
auto my_bme280 = TM_BME280_Class(true); // verbose = true -> print to serial

#include "TM_MH-Z19_Class.h"
auto my_mh_z19 = TM_MH_Z19_Class(true); // verbose = true -> print to serial

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ; // time to get serial running
    sensor.addTag("device", DEVICENAME);
    sensor.addTag("room", TAG_ROOM);
    TM_connect_wifi(DEVICENAME);
    TM_connect_influxdb();

    my_bme280.init();

    if (DEVICENAME == "T-ESP32-1")
    {
        my_mh_z19.init();
    }
}

void loop()
{
    float *TM_BME280_data = my_bme280.read_values();
    // 0 = T, 1 = Humidity, 2 = Pressure

    sensor.clearFields();
    sensor.addField("temperature", TM_BME280_data[0]);
    sensor.addField("humidity", TM_BME280_data[1]);
    sensor.addField("pressure", TM_BME280_data[2]);
    if (DEVICENAME == "T-ESP32-1")
    {
        int TM_MHZ_CO2 = my_mh_z19.read_values();
        sensor.addField("CO2", TM_MHZ_CO2);
    }
    TM_influx_send_point(sensor);

    delay(60000); // 60s
    // delay(1000); //TODO
}
