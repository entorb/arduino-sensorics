#include <Arduino.h>

// here the parameters for my device are set: name, room, as well als verbose mode
#include "device_setup.h"
#include "TM_Helper.h"

#include "TM_ESP32_Class.h"
auto my_esp32 = TM_ESP32_Class(myVerbose);

#ifdef TM_LOAD_DEVICE_INFLUXDB
#include "TM_InfluxDB_Class.h"
#include <InfluxDbClient.h>
auto my_influx = TM_Influx_Class(myVerbose);
Point sensor("Raumklima"); // TODO: -> my_sensor
#endif

#ifdef TM_LOAD_DEVICE_BME280
#include "TM_BME280_Class.h"
auto my_bme280 = TM_BME280_Class(myVerbose);
float *data_bme280;
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
#include "TM_MH_Z19_Class.h"
// Attention from EPS32 point of view the RX and TX are swapped, RX(MH-Z19)=TX(ESP32) and vice versa
auto my_mh_z19 = TM_MH_Z19_Class(14, 13, myVerbose);
uint16_t data_mhz_CO2;
#endif

#ifdef TM_LOAD_DEVICE_OLED_128X32
#include "TM_OLED_Class.h"
auto my_oled = TM_OLED_128x32_Class(myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_OLED_128X64
#include "TM_OLED_Class.h"
auto my_oled = TM_OLED_128x64_Class(myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
#include "TM_LED_Ring_Class.h"
auto my_led_ring = TM_LED_Ring_Class(15, 8, myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_LED_KY_016
#include "TM_LED_KY_016_Class.h"
//#include <analogWrite.h>
//#include "RGBLed.h"
auto my_led_ky_016 = TM_LED_KY_016_Class(5, 18, 19, myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_7_SEGMENT
#include "TM_7SegmentDisplay_Class.h"
auto my_7segment = TM_7SegmentDisplay_Class(32, 33, myVerbose);
#endif

// variables
uint8_t loopNum = 0;
uint32_t timeStart;
float data_to_display = 0;
const float value_min_CO2 = 400;
const float value_max_CO2 = 1000;

//
//
//
//

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // time to get serial running

// TODO: check if TM_LOAD_LED_KY_016 compatible with underclocking
#if !defined(TM_LOAD_DEVICE_LED_RING) && !defined(TM_LOAD_DEVICE_LED_KY_016)
  my_esp32.underclocking(); // underclocking breaks Adafruit_NeoPixel !!!
#endif

#ifdef TM_LOAD_DEVICE_INFLUXDB
  my_influx.connect_wifi(my_device_name);
  my_influx.sync_time();
  my_influx.connect_influxdb();
  sensor.addTag("device", my_device_name);
  sensor.addTag("room", my_room);
#endif

#ifdef TM_LOAD_DEVICE_BME280
  my_bme280.init();
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
  my_mh_z19.init();
#endif

#if defined(TM_LOAD_DEVICE_OLED_128X32) || defined(TM_LOAD_DEVICE_OLED_128X64)
  my_oled.init();
  my_oled.setBarChartRange(value_min_CO2, value_max_CO2); // = my_oled.setValueRange(value_min_CO2, value_max_CO2);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
  my_led_ring.init();
  my_led_ring.my_pixels.setBrightness(8);
  my_led_ring.setValueRange(value_min_CO2, value_max_CO2);
#endif

#ifdef TM_LOAD_DEVICE_LED_KY_016
  my_led_ky_016.init();
  // TODO: setBrightness
  my_led_ky_016.setValueRange(value_min_CO2, value_max_CO2);
#endif

#ifdef TM_LOAD_DEVICE_7_SEGMENT
  my_7segment.setValueRange(value_min_CO2, value_max_CO2);
#endif
} // end setup

//
//
//
//

void loop()
{
  timeStart = millis();
  data_to_display = loopNum; // dummy in case we have no sensor
  if (myVerbose)
  {
    // Serial.print("Start Loop: ");
    // Serial.println(loopNum);
  }

#ifdef TM_LOAD_DEVICE_INFLUXDB
  sensor.clearFields();
#endif

#ifdef TM_LOAD_DEVICE_BME280
  data_bme280 = my_bme280.read_values();
  // 0 = T, 1 = Humidity, 2 = Pressure
#ifdef TM_LOAD_DEVICE_INFLUXDB
  sensor.addField("temperature", data_bme280[0]);
  sensor.addField("humidity", data_bme280[1]);
  sensor.addField("pressure", data_bme280[2]);
#endif
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
  data_mhz_CO2 = my_mh_z19.read_values();
  data_to_display = data_mhz_CO2;
#ifdef TM_LOAD_DEVICE_INFLUXDB
  sensor.addField("CO2", data_mhz_CO2);
#endif
#endif
#ifdef TM_LOAD_DEVICE_INFLUXDB
  my_influx.send_point(sensor);
#endif

#if defined(TM_LOAD_DEVICE_OLED_128X32) || defined(TM_LOAD_DEVICE_OLED_128X64)
  // my_oled.draw_alternating_barchart_and_value(data_to_display);
  my_oled.drawBarchart(data_to_display);
  //uint8_t hour = getHour();
  // if (hour <= 21 && hour >= 7)
  // {
  //   my_oled.ensure_wake();
  //   // my_oled.draw_alternating_barchart_and_value(data_to_display);
  //   my_oled.drawBarchart(data_to_display);
  // }
  // else
  // {
  //   my_oled.ensure_sleep();
  // }
  //  my_oled.draw_alternating_barchart_and_value(data_to_display);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
  my_led_ring.displayValue(data_to_display);
#endif

#ifdef TM_LOAD_DEVICE_LED_KY_016
  my_led_ky_016.displayValue(data_to_display);
#endif

  // data_to_display = loopNum * 50;
#ifdef TM_LOAD_DEVICE_7_SEGMENT
  my_7segment.displayValueAndSetBrightness(data_to_display);
#endif

  // Serial.print("Loop: ");
  // Serial.print(loopNum);
  // Serial.print("value: ");
  // Serial.println(data_to_display);
  // Serial.print(" cat: ");

  //
  if (loopNum > 30)
    loopNum = 0;
  else
    loopNum++;
  sleep_exact_time(timeStart, millis());
} // end loop

//
//
//
//
//
//
//
//
// -----------------
// my helpers
// -----------------
//

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
    // usually 0.1-0.2sec for one loop of reading my_bme280 and my_mh_z19 and pushing to InfluxDB
  }
}

#include "time.h"
byte getHour()
// returns hour (00..23), if unknown returns 12
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time, returning 12");
    return 12; //-1;
  }
  return timeinfo.tm_hour;
}

// not used any more
/*
  void printLocalTime()
  {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
  }
*/
