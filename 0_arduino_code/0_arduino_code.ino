// here the parameters for my device are set: name, room, as well als verbose mode
#include "device_setup.h"

#include <Arduino.h>

#include "TM_ESP32_Class.h"
auto my_esp32 = TM_ESP32_Class();

#ifdef TM_LOAD_DEVICE_INFLUXDB
#include "TM_InfluxDB_Class.h"
#include <InfluxDbClient.h>
auto my_influx = TM_Influx_Class();
Point sensor("Raumklima");  // TODO: -> my_sensor
#endif

#ifdef TM_LOAD_DEVICE_BME280
#include "TM_BME280_Class.h"
auto my_bme280 = TM_BME280_Class();
float *data_bme280;
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
#include "TM_MH-Z19_Class.h"
auto my_mh_z19 = TM_MH_Z19_Class();
int data_mhz_CO2;
#endif

#ifdef TM_LOAD_DEVICE_OLED_128X32
#include "TM_OLED_Class.h"
auto my_oled = TM_OLED_128x32_Class();
#endif

#ifdef TM_LOAD_DEVICE_OLED_128X64
#include "TM_OLED_Class.h"
auto my_oled = TM_OLED_128x64_Class();
#endif

#ifdef TM_LOAD_LED_RING
#include "TM_LED_Ring_Class.h"
auto my_led_ring = TM_LED_Ring_Class();
#endif

// variables
unsigned int loopNum = 0;
unsigned long timeStart;
float data_to_display = 0;





void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // time to get serial running

  my_esp32.setVerbose(myVerbose);
#ifndef TM_LOAD_LED_RING
  my_esp32.underclocking(); // underclocking breaks Adafruit_NeoPixel !!!
#endif

#ifdef TM_LOAD_DEVICE_INFLUXDB
  my_influx.setVerbose(myVerbose);
  my_influx.connect_wifi(my_device_name);
  my_influx.sync_time();
  my_influx.connect_influxdb();
  sensor.addTag("device", my_device_name);
  sensor.addTag("room", my_room);
#endif

#ifdef TM_LOAD_DEVICE_BME280
  my_bme280.setVerbose(myVerbose);
  my_bme280.init();
#endif

#ifdef TM_LOAD_DEVICE_MHZ19
  my_mh_z19.setVerbose(myVerbose);
  my_mh_z19.init();
#endif

#if defined(TM_LOAD_DEVICE_OLED_128X32) || defined(TM_LOAD_DEVICE_OLED_128X64)
  my_oled.setVerbose(myVerbose);
  my_oled.init();
  my_oled.setBarchartRange(400, 1000); // for ppm
#endif

#ifdef TM_LOAD_LED_RING
  my_led_ring.setVerbose(myVerbose);
  my_led_ring.init();
  my_led_ring.my_pixels.begin();
  my_led_ring.setValueRange(400, 1000); // for ppm
#endif


} // end setup










void loop()
{
  timeStart = millis();
  data_to_display = loopNum; // dummy in case we have no sensor
  if (myVerbose) {
    Serial.print("Start Loop: ");
    Serial.println(loopNum);
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
  /*
    if (getHour() <= 21 && getHour() >= 7 ) {
      my_oled.ensure_wake();
      my_oled.drawAltBarchartOrInt(float(data_to_display));
    } else {
      my_oled.ensure_sleep();
    }
  */
  my_oled.drawAltBarchartOrInt(float(data_to_display));
#endif

#ifdef TM_LOAD_LED_RING
  my_led_ring.displayValue(data_to_display);
#endif


  loopNum ++;
  sleep_exact_time(timeStart, millis());
} // end loop







// my helpers


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
    return 12 ; //-1;
  }
  return timeinfo.tm_hour ;
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
