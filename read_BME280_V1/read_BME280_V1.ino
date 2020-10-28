
#include "TM_InfluxDB.h"
// InfluxDB Setup
#define MEASUREMENT "bme280"
// #1
// #define DEVICENAME "T-ESP32-1"
// #define TAG_ROOM "Schlafzimmer"
// #2
#define DEVICENAME "T-ESP32-2"
#define TAG_ROOM "Eleen"
// #3
// #define DEVICENAME "T-ESP32-3"
// #define TAG_ROOM "Hanno"

Point sensor(MEASUREMENT);

#include "TM_BME280.h"
//float TM_BME280_data[3];

#include "TM_MH-Z19.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ; // time to get serial running
    sensor.addTag("device", DEVICENAME);
    sensor.addTag("room", TAG_ROOM);
    TM_connect_wifi(DEVICENAME);
    TM_connect_influxdb();

    TM_BME280_init();

    if (DEVICENAME == "T-ESP32-1")
    {
        TM_MHZ19_init();
    }
}

void loop()
{
    float *TM_BME280_data = TM_BME280_read_values(true);
    // 0 = T, 1 = Humidity, 2 = Pressure
    int TM_MHZ_CO2 = TM_MHZ19_read_values(true);

    sensor.clearFields();
    sensor.addField("temperature", TM_BME280_data[0]);
    sensor.addField("humidity", TM_BME280_data[1]);
    sensor.addField("pressure", TM_BME280_data[2]);
    if (DEVICENAME == "T-ESP32-1")
    {
        sensor.addField("CO2", TM_MHZ_CO2);
    }
    TM_influx_send_point(sensor);

    delay(60000); // 60s
    // delay(1000); //TODO
}
