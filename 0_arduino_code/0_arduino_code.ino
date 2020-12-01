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
Point influx_data_set("Raumklima"); // Table
#endif

#ifdef TM_LOAD_DEVICE_BME280
#include "TM_BME280_Class.h"
auto my_sensor_bme280 = TM_BME280_Class(myVerbose);
float *data_bme280;
#endif

#ifdef TM_LOAD_DEVICE_BME680
#include "TM_BME680_Class.h"
auto my_sensor_bme680 = TM_BME680_Class(myVerbose);
float *data_bme680;
#endif

#ifdef TM_LOAD_DEVICE_BH1750
#include "TM_BH1750_Class.h"
auto my_sensor_illuminance = TM_BH1750_Class(myVerbose);
float data_lux;
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
#include "TM_MH_Z19_Class.h"
// Attention from EPS32 point of view the RX and TX are swapped, RX(MH-Z19)=TX(ESP32) and vice versa
// auto my_sensor_CO2 = TM_MH_Z19_Class(14, 13, myVerbose);
// auto my_sensor_CO2 = TM_MH_Z19_Class(16, 17, myVerbose);
auto my_sensor_CO2 = TM_MH_Z19_Class(TM_MHZ19_PIN_RX, TM_MHZ19_PIN_TX, myVerbose);
uint8_t count_same_CO2_values = 0; // MH-Z19 and WiFi/InfluxDB have a problem, that when both are enabled, the MH-Z19 from time to time is stuck and returns always a value of 380
uint16_t data_CO2;
#endif

#ifdef TM_LOAD_DEVICE_4_DIGIT
#include "TM_4DigitDisplay_Class.h"
auto my_display_4digit = TM_4DigitDisplay_Class(32, 33, myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_OLED_128X32
#include "TM_OLED_Class.h"
auto my_display_oled = TM_OLED_128x32_Class(myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_OLED_128X64
#include "TM_OLED_Class.h"
auto my_display_oled = TM_OLED_128x64_Class(myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
#include "TM_LED_Ring_Class.h"
auto my_display_led_rbg_ring = TM_LED_Ring_Class(15, 8, myVerbose);
#endif

#ifdef TM_LOAD_DEVICE_LED_KY_016
#include "TM_LED_KY_016_Class.h"
//#include <analogWrite.h>
//#include "RGBLed.h"
auto my_display_led_rbg_single = TM_LED_KY_016_Class(5, 18, 19, myVerbose);
#endif

// variables
uint8_t loopNum = 0;
uint32_t timeStart;
float data_to_display = 0;

const float value_min_CO2 = 400;
const float value_max_CO2 = 1000;
// 3 colors for 600 values -> blue for 600-800

bool display_shall_sleep = false;
//
//
//
//

void setup()
{
  Serial.begin(115200);
  // Fuck: This sometimes results in an endless wait if not connected to PC
  // while (!Serial)
  //   ; // time to get serial running
  // Serial.flush();

#if !defined(TM_LOAD_DEVICE_LED_RING)
  my_esp32.underclocking(); // underclocking breaks Adafruit_NeoPixel !!!
#endif
  my_esp32.init();

#ifdef TM_LOAD_DEVICE_INFLUXDB
  my_influx.connect_wifi(my_device_name);
#if defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE)
  my_influx.sync_time();
#endif
  my_influx.connect_influxdb();
  influx_data_set.addTag("device", my_device_name);
  influx_data_set.addTag("room", my_room);
#endif

#ifdef TM_LOAD_DEVICE_BME280
  my_sensor_bme280.init();
#endif

#ifdef TM_LOAD_DEVICE_BME680
  my_sensor_bme680.init();
#endif

#ifdef TM_LOAD_DEVICE_BH1750
  my_sensor_illuminance.init();
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
  my_sensor_CO2.init();
#endif

#if defined(TM_LOAD_DEVICE_OLED_128X32) || defined(TM_LOAD_DEVICE_OLED_128X64)
  my_display_oled.init();
  my_display_oled.setBarChartRange(value_min_CO2, value_max_CO2); // = my_display_oled.setValueRange(value_min_CO2, value_max_CO2);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
  my_display_led_rbg_ring.init();
  my_display_led_rbg_ring.my_pixels.setBrightness(8);
  my_display_led_rbg_ring.setValueRange(value_min_CO2, value_max_CO2);
#endif

#ifdef TM_LOAD_DEVICE_LED_KY_016
  my_display_led_rbg_single.init();
  my_display_led_rbg_single.setValueRange(value_min_CO2, value_max_CO2);
#endif

#ifdef TM_LOAD_DEVICE_4_DIGIT
  my_display_4digit.init();
  my_display_4digit.setValueRange(value_min_CO2, value_max_CO2);
  my_display_4digit.displayValue(9000); // Displaying a value of 9000 for debugging purposes
  // delay(1000);
#endif
} // end setup

//
//
//
//

void loop()
{
  timeStart = millis();
  data_to_display = 8000 + loopNum; // dummy in case we have no sensor
  // delay(1000);

  display_shall_sleep = false; // set to on by default in each loop

#ifdef TM_LOAD_DEVICE_INFLUXDB
  influx_data_set.clearFields();
  // we only know the time if clock is initially set via WiFi and NTP
#if defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE)
  uint8_t hour = getHour();
  if (hour < TM_HOUR_WAKE || hour >= TM_HOUR_SLEEP)
  {
    display_shall_sleep = true;
  }
#endif
#endif

#ifdef TM_LOAD_DEVICE_BME280
  data_bme280 = my_sensor_bme280.read_values();
  // 0 = Temp, 1 = Humidity, 2 = Pressure
#ifdef TM_LOAD_DEVICE_INFLUXDB
  if (data_bme280[0] > -100) // Temp must be larger than -100°C, else -> discard
  {
    influx_data_set.addField("temperature", data_bme680[0]);
    influx_data_set.addField("humidity", data_bme680[1]);
    influx_data_set.addField("pressure", data_bme680[2]);
  }
#endif
#endif

#ifdef TM_LOAD_DEVICE_BME680
  data_bme680 = my_sensor_bme680.read();
  // data[0] = iaqSensor.rawTemperature;
  // data[1] = iaqSensor.temperature;
  // data[2] = iaqSensor.rawHumidity;
  // data[3] = iaqSensor.humidity;
  // data[4] = iaqSensor.pressure;
  // data[5] = iaqSensor.gasResistance;
  // data[6] = iaqSensor.iaq;
  // data[7] = iaqSensor.iaqAccuracy;
  // data[8] = iaqSensor.staticIaq;
  // data[9] = iaqSensor.co2Equivalent;
  // data[10] = iaqSensor.breathVocEquivalent;

#ifdef TM_LOAD_DEVICE_INFLUXDB
  if (data_bme680[1] > -100) // Temp must be larger than -100°C, else -> discard
  {
    influx_data_set.addField("temperature", data_bme680[1]);
    influx_data_set.addField("humidity", data_bme680[3]);
    influx_data_set.addField("pressure", data_bme680[4]);
    influx_data_set.addField("bme680_gasResistance", data_bme680[5]);
    influx_data_set.addField("bme680_iaq", data_bme680[6]);
    influx_data_set.addField("bme680_iaqAccuracy", data_bme680[7]);
    influx_data_set.addField("bme680_staticIaq", data_bme680[8]);
    influx_data_set.addField("bme680_co2Equivalent", data_bme680[9]);
    influx_data_set.addField("bme680_breathVocEquivalent", data_bme680[10]);
  }
#endif
#endif

#ifdef TM_LOAD_DEVICE_BH1750
  data_lux = my_sensor_illuminance.read();
#ifdef TM_LOAD_DEVICE_INFLUXDB
  influx_data_set.addField("illuminance", data_lux);
#endif
  if (display_shall_sleep == false and data_lux <= 10)
    display_shall_sleep = true;
  else
    display_shall_sleep = false;
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
  if (millis() < 10 * 1000) // start is not reliable, so ignored
  {
    if (myVerbose)
    {
      Serial.println("not reading CO2 yet");
    }
  }
  else // normal mode
  {
    data_CO2 = my_sensor_CO2.read_values();
    // my_display_4digit.displayValue(7000 + data_CO2); // TODO
    // delay(1000);

    // special handling for values of 0 and 380pmm
    // MH-Z19 sometimes is interrupted by WiFi/InfluxDB or missing serial connection, resulting in always returning the same values,
    // Workaround V1: retrying after a random sleep
    if (data_CO2 == 0 || data_CO2 == 380)
    {
      if (myVerbose)
      {
        Serial.println("0 or 380ppm -> re-reading");
      }
      delay(random(100, 500));
      data_CO2 = my_sensor_CO2.read_values();
    }

    // Workaround V2: rebooting after 10x the same CO2 values of 0 or 380ppm
    if (data_CO2 == 0 || data_CO2 == 380)
    {
      count_same_CO2_values++;
      if (count_same_CO2_values >= 10)
      {
        Serial.println("restarting");
        my_esp32.restart();
      }
    }
    else
    {
      count_same_CO2_values = 0;
    }
    data_to_display = data_CO2;
  }
#ifdef TM_LOAD_DEVICE_INFLUXDB
  influx_data_set.addField("CO2", data_CO2);
#endif

#endif

#ifdef TM_LOAD_DEVICE_INFLUXDB
  my_influx.send_point(influx_data_set);
#endif

#if defined(TM_LOAD_DEVICE_OLED_128X32) || defined(TM_LOAD_DEVICE_OLED_128X64)
  // my_display_oled.draw_alternating_barchart_and_value(data_to_display);
  if (display_shall_sleep == false)
  {
    my_display_oled.ensure_wake();
    my_display_oled.drawBarChart(data_to_display);
  }
  else
  {
    my_display_oled.ensure_sleep();
    my_display_oled.appendValueToBarChart(data_to_display);
  }

//uint8_t hour = getHour();
// if (hour <= 21 && hour >= 7)
// {
//   my_display_oled.ensure_wake();
//   // my_display_oled.draw_alternating_barchart_and_value(data_to_display);
//   my_display_oled.drawBarChart(data_to_display);
// }
// else
// {
//   my_display_oled.ensure_sleep();
// }
//  my_display_oled.draw_alternating_barchart_and_value(data_to_display);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
  my_display_led_rbg_ring.displayValue(data_to_display);
#endif

#ifdef TM_LOAD_DEVICE_LED_KY_016
  my_display_led_rbg_single.displayValue(data_to_display);
#endif

// data_to_display = loopNum * 50;
#ifdef TM_LOAD_DEVICE_4_DIGIT
  if (display_shall_sleep == false)
  {
    my_display_4digit.ensure_wake();
    my_display_4digit.displayValueAndSetBrightness(data_to_display);
  }
  else
  {
    my_display_4digit.ensure_sleep();
  }
#endif

  // Serial.print("Loop: ");
  // Serial.print(loopNum);
  // Serial.print("value: ");
  // Serial.println(data_to_display);

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
    // usually 0.1-0.2sec for one loop of reading my_sensor_bme280 and my_sensor_CO2 and pushing to InfluxDB
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
