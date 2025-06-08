# Arduino-sensorics

* Arduino ESP32 micro-controller programming
* Provides simple and clean library for
  * reading of various sensors
  * export data via WiFi to InfluxDB for visualization in Grafana, see my [raspi-sensorics](https://github.com/entorb/raspi-sensorics/) repository
  * writing to various displays
  * using a device_setup.h file to select the devices attached to that specific Arduino ESP32
  * read data from MQTT

## Devices implemented so far

* Abstract device class that all other devices inherit from in [TM_Device_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_Device_Class.cpp)
* InfuxDB interface via WiFi in [TM_InfluxDB_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB_Class.cpp)
* BME280 sensor for temperature, humidity and pressure in [TM_BME280_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_BME280_Class.cpp)
* BH1750 sensor for illumination in [TM_BH1750_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_BH1750_Class.cpp)
* MH-Z19B sensor for CO2 concentration in [TM_MH_Z19_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_MH_Z19_Class.cpp)
* 7-segment 4-digit TM1637 display in [TM_7SegmentDisplay_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_7SegmentDisplay_Class.cpp)
* OLED display 128x32px and 128x64px in [TM_OLED_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_OLED_Class.h)
* RGB-LEDs: Ring and Single LED in [TM_LED_Ring_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_LED_Ring_Class.cpp)

## Arduino packages used

* [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library)
* [BH1750](https://github.com/claws/BH1750)
* [ESP8266 Influxdb](https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino)
* [MH-Z19](https://github.com/WifWaf/MH-Z19)
* [TM1637](https://github.com/avishorp/TM1637)
* [U8G2](https://github.com/olikraus/u8g2)
* [(MQTT) PubSubClient](https://github.com/knolleary/pubsubclient)

## Achievements

* Learning basics of C++: inheritance, templates, ...
* Using pre compiler #define in device_setup.h file to select which classes are compiled to save time and memory
* Power reduction from 1W to 0.3W by
  * Under-clocking the ESP32 from 240 to 80 MHz via setCpuFrequencyMhz(80) in ([TM_ESP32_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_ESP32_Class.cpp)
  * Enabling WiFi modem sleep via esp_wifi_set_ps(WIFI_PS_MODEM) in [TM_InfluxDB_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB_Class.cpp)
* OLED display: implemented bar chart
* Standalone CO2 traffic light for our kindergarden and school
  * offline
  * in proper case
  * using display and traffic light for visualization
  * see German [Bauanleitung](https://github.com/entorb/arduino-sensorics/blob/main/CO2-Ampel-Bauanleitung.md)
* Experiment with display devices

## Next steps

* Design and build cases via CAD and CNC
* Add more sensors

## Photos and screenshots

CO2 Traffic Light V1.2: Massproduction and added history bar chart via OLED display ([Bauanleitung](https://github.com/entorb/arduino-sensorics/blob/main/CO2-Ampel-Bauanleitung.md))
![4xCO2-in-Holz](https://github.com/entorb/arduino-sensorics/blob/main/photos/4xCO2-in-Holz.jpg)

CO2 Traffic Light V1 for our School ([Bauanleitung](https://github.com/entorb/arduino-sensorics/blob/main/CO2-Ampel-Bauanleitung.md))
![ASGS-V1.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ASGS-V1.jpg)

CO2 Traffic Light Prototype for our Kindergarten: Display of CO2 level (measured by MH-Z19B) on a 7-segment display and RGB-LED
![KiTa-V1.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/KiTa-V1.jpg)

Experimenting with different displays
![Display-Test.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/Display-Test.jpg)

Display of CO2 level on small OLED display (measured by MH-Z19B)
![ESP32-MHZ19-OLED128x32.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ESP32-MHZ19-OLED128x32.jpg)

Display of CO2 in Grafana (measured by MH-Z1B9)
![Grafana-CO2.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-CO2.png)

Display of temperature, humidity and pressure in Grafana (measured by BME280)
![Grafana-T-H-P.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-T-H-P.png)

## Similar projects

* [UN-Hack-Bar: CO2 Ampeln für alle](https://www.un-hack-bar.de/2020/10/25/co2-ampeln-fuer-alle/)
* [UN-Hack-Bar: Repository](https://git.unhb.de/smash/co2ampel)
* [Heise: CO2-Ampel: Bauanleitung](https://www.heise.de/select/make/2020/5/2022015381334973804)
* [Heise: CO2-Ampel: Erfahrungsbericht aus der Schule](https://www.heise.de/news/CO2-Ampel-Erfahrungsbericht-aus-der-Schule-4932471.html)
