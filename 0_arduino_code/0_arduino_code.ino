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
Point influx_data_set("Raumklima"); // Table Name
uint32_t timestampLastTimeSync;
uint8_t hour;
uint8_t minute;
#endif

#ifdef TM_LOAD_DEVICE_BME280
#include "TM_BME280_Class.h"
auto my_sensor_bme280 = TM_BME280_Class(myVerbose);
float *data_bme280;
#endif

#ifdef TM_LOAD_DEVICE_BME680
// for BME680 in LP mode, the loop sleep time must be 3s!
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
// new layout
// #define TM_MHZ19_PIN_RX 16
// #define TM_MHZ19_PIN_TX 17
// old KiTa layout
// #define TM_MHZ19_PIN_RX 14
// #define TM_MHZ19_PIN_TX 13
auto my_sensor_CO2 = TM_MH_Z19_Class(TM_MHZ19_PIN_RX, TM_MHZ19_PIN_TX, myVerbose);
uint8_t count_same_CO2_values = 0; // MH-Z19 and WiFi/InfluxDB have a problem, that when both are enabled, the MH-Z19 from time to time is stuck and returns always a value of 380
int data_CO2 = 0;
#endif

#ifdef TM_LOAD_DEVICE_4_DIGIT
#include "TM_4DigitDisplay_Class.h"
auto my_display_4digit = TM_4DigitDisplay_Class(32, 33, myVerbose);
int my_display_4digit_loop_delay = 0; // ms
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
const float value_max_CO2 = 1150;
// new: 400-1150: 3 colors for 750 values -> blue for 650-900
// old: 400-1000: 3 colors for 600 values -> blue for 600-800

bool display_shall_sleep = false;

//
//
// II. Setup
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
#if defined(TM_DISPLAY_TIME) || defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE)
  my_influx.sync_time();
  timestampLastTimeSync = getTimestamp();
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

#if defined(TM_DISPLAY_TIME)
  my_display_4digit_loop_delay += 1;
#endif
#if defined(TM_LOAD_DEVICE_MHZ19)
  my_display_4digit_loop_delay += 2; // twice the time than for the other values
#endif
#if defined(TM_LOAD_DEVICE_BME280)
  my_display_4digit_loop_delay += 2; // 2 values
#endif
  my_display_4digit_loop_delay = mySleep / my_display_4digit_loop_delay; // overwrite the counter by the resulting value in ms
  // delay(1000);
#endif
} // end setup

//
//
// III. Loop
//
//

void loop()
{
  timeStart = millis();
  data_to_display = 8000 + loopNum; // dummy in case we have no sensor

  display_shall_sleep = false; // set to on by default in each loop

//
// Influx: prepare empty dataset
//
#ifdef TM_LOAD_DEVICE_INFLUXDB
  influx_data_set.clearFields();
#endif

//
// sync time every 7 days, but only at loopNum=0 for reducing connection problem timeouts
//
#ifdef TM_LOAD_DEVICE_INFLUXDB
#if defined(TM_DISPLAY_TIME) || (defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE))
  if (loopNum == 0 && (getTimestamp() > timestampLastTimeSync + 24 * 3600 * 7))
  {
    my_influx.sync_time();
    timestampLastTimeSync = getTimestamp();
  }
#endif
#endif

//
// disable display if this is configured
// we only know the time if clock is initially set via WiFi and NTP
//
#ifdef TM_LOAD_DEVICE_INFLUXDB
#if defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE)
  // check if we are at sleeping time
  if (display_shall_sleep == false)
  {
    hour = getHour();
    if (hour < TM_HOUR_WAKE || hour >= TM_HOUR_SLEEP)
      display_shall_sleep = true;
  }
#endif
#endif

//
// 1. read sensors
//
// 1.1 BME280: T, H, P
#ifdef TM_LOAD_DEVICE_BME280
  data_bme280 = my_sensor_bme280.read_values();
  // 0 = Temp, 1 = Humidity, 2 = Pressure
#ifdef TM_LOAD_DEVICE_INFLUXDB
  if (data_bme280[0] > -100) // Temp must be larger than -100°C, else -> discard
  {
    influx_data_set.addField("temperature", data_bme280[0]);
    influx_data_set.addField("humidity", data_bme280[1]);
    influx_data_set.addField("pressure", data_bme280[2]);
  }
#endif
#endif

// 1.2 BME680: T, H, P, IAQ, ...
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

// 1.3 BH1750: Illuminance
#ifdef TM_LOAD_DEVICE_BH1750
  data_lux = my_sensor_illuminance.read();
#ifdef TM_LOAD_DEVICE_INFLUXDB
  influx_data_set.addField("illuminance", data_lux);
#endif
  if (display_shall_sleep == false && data_lux <= 1)
    display_shall_sleep = true;
#endif

// 1.4 MHZ19: CO2
#ifdef TM_LOAD_DEVICE_MHZ19
  if (millis() < 3 * 1000) // start is not reliable, so ignored
  {
    if (myVerbose)
    {
      Serial.println("not reading CO2 yet");
    }
  }
  else // normal mode
  {
    data_CO2 = my_sensor_CO2.read_values();

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

//
// 2. Displays
//

//
//  2.1 4-digit display
//

// 2.1.1 init
#ifdef TM_LOAD_DEVICE_4_DIGIT
  if (display_shall_sleep == true)
  {
    my_display_4digit.ensure_sleep();
  }
  else
  {
    my_display_4digit.ensure_wake();

// 2.1.2a CO2 only
#if defined(TM_LOAD_DEVICE_MHZ19) && !defined(TM_LOAD_DEVICE_BME280)
    my_display_4digit.displayValueAndSetBrightness(data_CO2);
    delay(2 * my_display_4digit_loop_delay); // twice the time than the other values
#endif

// 2.1.2b H, T only
#if !defined(TM_LOAD_DEVICE_MHZ19) && defined(TM_LOAD_DEVICE_BME280)
    my_display_4digit.setBrightness(1);
    my_display_4digit.displayValue2p1(data_bme280[1]); // H
    delay(my_display_4digit_loop_delay);
    my_display_4digit.displayValue2p1(data_bme280[0]); // T
    delay(my_display_4digit_loop_delay);
#endif

// 2.1.2c CO2, H, T
#if defined(TM_LOAD_DEVICE_MHZ19) && defined(TM_LOAD_DEVICE_BME280)
    // my_display_4digit.setBrightness(0);
    // for not on use same brightness for H and T as for CO2
    my_display_4digit.displayValueAndSetBrightness(data_CO2);
    delay(2 * my_display_4digit_loop_delay);           // twice the time than the other values
    my_display_4digit.displayValue2p1(data_bme280[1]); // H
    delay(my_display_4digit_loop_delay);
    my_display_4digit.displayValue2p1(data_bme280[0]); // T
    delay(my_display_4digit_loop_delay);
#endif
  }
#endif

// 2.1.3 time
#if defined(TM_LOAD_DEVICE_INFLUXDB)
#if defined(TM_DISPLAY_TIME) || defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE)
  hour = getHour();
  minute = getMinute();
  my_display_4digit.displayTime(hour, minute);
  delay(my_display_4digit_loop_delay);
#endif
#endif

  //
  //  2.2 LEDs
  //

#ifdef TM_LOAD_DEVICE_LED_KY_016
  if (display_shall_sleep == true)
    my_display_led_rbg_single.setColor(0, 0, 0, 0);
  else
    my_display_led_rbg_single.displayValue(data_CO2);
#endif

#ifdef TM_LOAD_DEVICE_LED_RING
  if (display_shall_sleep == true)
    my_display_led_rbg_ring.displayValue(0);
  else
    my_display_led_rbg_ring.displayValue(data_CO2);
#endif

    //
    // 2.3 OLED Bar Chart
    //

#if defined(TM_LOAD_DEVICE_OLED_128X32) || defined(TM_LOAD_DEVICE_OLED_128X64)
  if (display_shall_sleep == true)
  {
    my_display_oled.ensure_sleep();
    my_display_oled.appendValueToBarChart(data_CO2);
  }
  else
  {
    my_display_oled.ensure_wake();
    my_display_oled.drawBarChart(data_CO2);
  }

#endif

  //
  // 3. send data to InfluxDB
  //

#ifdef TM_LOAD_DEVICE_INFLUXDB
  my_influx.send_point(influx_data_set);
#endif

  //
  // 4. End of Loop
  //

  if (loopNum >= 31) // must be a multiple of 4 minus 1
    loopNum = 0;
  else
    loopNum++;
  sleep_exact_time(timeStart, mySleep);

} // end loop

//
//
// IV. Helpers
//
//

void sleep_exact_time(const unsigned long timeStart, const unsigned long duration)
{
  const unsigned long timeEnd = millis();
  // calc delay time based on start and stop
  if (timeEnd < timeStart)
  { // overrun of millis() happened
    delay(duration);
  }
  else if (timeEnd > timeStart + duration)
  { // loop took too long -> no sleep
  }
  else
  { // normal case
    delay(duration - (timeEnd - timeStart));
    // usually 0.1-0.2sec for one loop of reading my_sensor_bme280 and my_sensor_CO2 and pushing to InfluxDB
  }
}

#ifdef TM_LOAD_DEVICE_INFLUXDB
#if defined(TM_DISPLAY_TIME) || defined(TM_HOUR_SLEEP) && defined(TM_HOUR_WAKE)

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

byte getMinute()
// returns minutes (00..59), if unknown returns 0
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time, returning 00");
    return 0; //-1;
  }
  return timeinfo.tm_min;
}

unsigned long getTimestamp()
// returns unix timestamp, if not successful returns 0
{
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain timestamp, returning 0");
    return (0);
  }
  time(&now);
  return now;
}
#endif
#endif