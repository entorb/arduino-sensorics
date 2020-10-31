# arduino-sensorics
Reading various sensors and using divices attached to an Arduino ESP32 micro-controller.  
Data is uploaded via WiFi to an InfluxDB on a Raspberry Pi 3 Model B and visualized via Grafana, see my [raspi-sensorics](https://github.com/entorb/raspi-sensorics/) repository

## Devices implemented so far
* Abstract device class that all other devices inherit from in [TM_Device_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_Device_Class.cpp)
* BME280 sensor for temperature, humidity and pressure in [TM_BME280_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_BME280_Class.cpp)
* MH-Z19 sensor for CO2 concentration in [TM_MH-Z19_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_MH-Z19_Class.cpp)
* OLED display 128x32px in [TM_OLED_128x32.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_OLED_128x32.cpp)
* InfuxDB interface via WiFi in [TM_InfluxDB.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB.cpp)

## Achievements 
* Using pre compiler #define in device_setup.h file to select which classes are compiled to save time and memory
* Power reduction from 1W to 0.3W by
  * Under-clocking the ESP32 from 240 to 80 MHz via setCpuFrequencyMhz(80) in ([TM_ESP32-Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_ESP32-Class.cpp)
  * Enabling WiFi modem sleep via esp_wifi_set_ps(WIFI_PS_MODEM) in [TM_InfluxDB.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB.cpp)

## Photos and Screenshots
Reading MH-Z19 CO2 sensor and displaying on small OLED display
![ESP32-MHZ19-OLED128x32.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ESP32-MHZ19-OLED128x32.jpg)

Display of CO2 in Grafana (measured by MH-Z19)
![Grafana-CO2.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-CO2.png)

Display of temperature, humidity and pressure in Grafana (measured by BME280)
![Grafana-CO2.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-CO2.png)

