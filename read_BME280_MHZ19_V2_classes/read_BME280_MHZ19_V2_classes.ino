#include <Arduino.h>

// setup of this device
static const int mySleep = 60*1000; // milli sec

// InfluxDB Setup
#define MEASUREMENT "Raumklima"

// #1
#define DEVICENAME "T-ESP32-1"
#define TAG_ROOM "Arbeitszimmer"
// #2
//#define DEVICENAME "T-ESP32-2"
//// #define TAG_ROOM "Kind 1"
//#define TAG_ROOM "Wintergarten"
// #3
// #define DEVICENAME "T-ESP32-3"
// // #define TAG_ROOM "Kind 2"
// #define TAG_ROOM "Bad"

// Power
#include "esp32-hal-cpu.h" // for getCpuFrequencyMhz

// InfluxDB
#include "TM_InfluxDB.h"
#include <InfluxDbClient.h>
auto my_influx = TM_Influx_Class();
Point sensor(MEASUREMENT);

#include "TM_BME280_Class.h"
auto my_bme280 = TM_BME280_Class();

#include "TM_MH-Z19_Class.h"
auto my_mh_z19 = TM_MH_Z19_Class();

// variables
float *data_bme280;
int data_mhz_CO2;
unsigned long timeStart;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // time to get serial running

  setCpuFrequencyMhz(80); // for power saving
  // Serial.println( getCpuFrequencyMhz() );

  sensor.addTag("device", DEVICENAME);
  sensor.addTag("room", TAG_ROOM);
  my_influx.connect_wifi(DEVICENAME);
  my_influx.connect_influxdb();

  // my_bme280.setVerbose(true); // verbose = true -> print to serial
  my_bme280.init();

  if (DEVICENAME == "T-ESP32-1")
  {
    // my_mh_z19.setVerbose(true); // verbose = true -> print to serial
    my_mh_z19.init();
  }
}

void loop()
{
  timeStart = millis();
  data_bme280 = my_bme280.read_values();
  // 0 = T, 1 = Humidity, 2 = Pressure

  sensor.clearFields();
  sensor.addField("temperature", data_bme280[0]);
  sensor.addField("humidity", data_bme280[1]);
  sensor.addField("pressure", data_bme280[2]);
  if (DEVICENAME == "T-ESP32-1")
  {
    data_mhz_CO2 = my_mh_z19.read_values();
    sensor.addField("CO2", data_mhz_CO2);
  }
  my_influx.send_point(sensor);

  sleep_exact_time(timeStart, millis());
}

void sleep_exact_time(const unsigned long timeStart, const unsigned long timeEnd)
{
  // calc delay time based on start and stop
  if (timeEnd < timeStart)
  { // overrun of millis() happened
    delay(mySleep);
  }
  else if (timeEnd > timeStart + mySleep)
  {
    // no delay / sleep
  }
  else
  {
    delay(mySleep - (timeEnd - timeStart));
    // usually .1-.2sec for one loop of reading my_bme280 and my_mh_z19 and pushing to InfluxDB
  }
}
