# arduino-sensorics
Code for reading various sensors attached to an Arduino ESP32 micro-controller.  
Data is uploaded via WiFi to an InfluxDB on a Raspberry Pi 3b and visualized via Grafana, see https://github.com/entorb/raspi-sensorics/ 

# Devices implemented
* Abstract device class that all other devices inherit from in [TM_Device_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_Device_Class.cpp)
* BME280 sensor for temperature, humidity and pressure in [TM_BME280_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_BME280_Class.cpp)
* MH-Z19 sensor for CO2 concentration in [TM_MH-Z19_Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_MH-Z19_Class.cpp)
* OLED display 128x32px in [TM_OLED_128x32.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_OLED_128x32.cpp)
* InfuxDB interface via WiFi in [TM_InfluxDB.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB.cpp)

# Achievements 
* Using pre compiler #define in device_setup.h file to select which classes are compiled to save time and memory
* Power reduction from 1W to 0.3W by
** Under-clocking the ESP32 from 240 to 80 MHz via setCpuFrequencyMhz(80) in ([TM_ESP32-Class.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_ESP32-Class.cpp)
** Enabling WiFi modem sleep via esp_wifi_set_ps(WIFI_PS_MODEM) in [TM_InfluxDB.cpp](https://github.com/entorb/arduino-sensorics/blob/main/libraries/TM/src/TM_InfluxDB.cpp)

