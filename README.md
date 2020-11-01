# arduino-sensorics
* Arduino ESP32 micro-controller programming
* provides simple and clean library for 
  * reading of various sensors
  * export data via WiFi to InfluxDB for visualization in Grafana, see my [raspi-sensorics](https://github.com/entorb/raspi-sensorics/) repository
  * writing to various displays
  * using a config.h file to select the devices available to that Arduino

## Devices implemented so far
* BME280 sensor for temperature, humidity and pressure in [TM_BME280_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_BME280_Class.cpp)
* MH-Z19 sensor for CO2 concentration in [TM_MH-Z19_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_MH-Z19_Class.cpp)
* OLED display 128x32px in [TM_OLED_128x32.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_OLED_128x32.cpp)
* InfuxDB interface via WiFi in [TM_InfluxDB.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB.cpp)
* Abstract device class that all other devices inherit from in [TM_Device_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_Device_Class.cpp)

## Achievements 
* Using pre compiler #define in device_setup.h file to select which classes are compiled to save time and memory
* Power reduction from 1W to 0.3W by
  * Under-clocking the ESP32 from 240 to 80 MHz via setCpuFrequencyMhz(80) in ([TM_ESP32-Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_ESP32-Class.cpp)
  * Enabling WiFi modem sleep via esp_wifi_set_ps(WIFI_PS_MODEM) in [TM_InfluxDB.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB.cpp)
* OLED display: alternating display of value and bar chart

## Next steps
* standalone CO2 traffic light for our kindergarden and school
  * offline version, display only
  * in proper case
  * using display and traffic light for visualization
* experiment with more display units
* design and build cases
* add more sensors

## Photos and screenshots
Display of CO2 level on small OLED display (measured by MH-Z19)
![ESP32-MHZ19-OLED128x32.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ESP32-MHZ19-OLED128x32.jpg)

Display of CO2 in Grafana (measured by MH-Z19)
![Grafana-CO2.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-CO2.png)

Display of temperature, humidity and pressure in Grafana (measured by BME280)
![Grafana-T-H-P.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-T-H-P.png)

## Similar projects
* [UN-Hack-Bar: CO2 Ampeln für alle](https://www.un-hack-bar.de/2020/10/25/co2-ampeln-fuer-alle/)
* [UN-Hack-Bar: Repository](https://git.unhb.de/smash/co2ampel)
* [Heise: CO2-Ampel: Bauanleitung](https://www.heise.de/select/make/2020/5/2022015381334973804)
* [Heise: CO2-Ampel: Erfahrungsbericht aus der Schule](https://www.heise.de/news/CO2-Ampel-Erfahrungsbericht-aus-der-Schule-4932471.html)
