# Arduino Sensorics

Arduino ESP32 sensor platform. Reads BME280/BME680/BH1750/MH-Z19, writes TM1637/OLED/RGB-LED, sends to InfluxDB 1.x, reads MQTT.

## Build & Config

**Board**: `esp32` (Arduino core 3.0.3). No Makefile/CMake — open [0_arduino_code/0_arduino_code.ino](0_arduino_code/0_arduino_code.ino) in Arduino IDE.

**Device config**: `device_setup.h` — `#define TM_LOAD_DEVICE_*` to enable sensors/displays.

**Secrets**: `*_secret.h` in gitignore, templates in `*-example.h`. Required: `TM_WiFi_secret.h`, `TM_InfluxDB_secret.h`, `TM_MQTT_secret.h` in `libraries/TM/src/`.

**No CI, no test framework**.

## Custom Library (`libraries/TM/`)

Only library tracked in git. Prefix `TM_`, hierarchy from `TM_Device_Class`:

- **Display**: `TM_4DigitDisplay_Class` (TM1637, pins 32/33), `TM_OLED_Class` (template, aliases `TM_OLED_128x32/64_Class`), `TM_LED_KY_016_Class` (RGB 5/18/19), `TM_LED_Ring_Class` (WS2812, pin 15)
- **Sensor**: `TM_BME280_Class` (I2C 0x76 → T/H/P float[3]), `TM_BH1750_Class`, `TM_MH_Z19_Class` (UART → CO2 int), `TM_BME680_Class` (11-value float[], BSEC lib)
- **Infra**: `TM_ESP32_Class` (underclock 80MHz, restart), `TM_Influx_Class` (WiFi+InfluxDB 1.x, rate-limited), `TM_MQTT_Class` (stub, TODO)

`.txt` source files (BME680, LED_Ring) are drafts — not compiled.

## ESP32 Quirks

- **Underclock**: `my_esp32.underclocking()` → 80MHz. Skip if WS2812 (NeoPixel breaks at 80MHz).
- **WiFi power**: `WIFI_PS_MAX_MODEM` set in `TM_InfluxDB_Class`.
- **CO2**: values 0/380 → re-read after random(100,500)ms delay; after 10 consecutive → reboot.
- **Loop**: `sleep_exact_time(timeStart, mySleep)` — overflow-safe unsigned math.
- **Night**: `TM_HOUR_SLEEP`/`TM_HOUR_WAKE` → display off, sensors/InfluxDB still run.

## Pin Quick Ref

| Device | Pins |
| ------ | ---- |
| I2C (BME280, OLED, BH1750) | SCL=22, SDA=21 |
| MH-Z19 (new) | RX=16, TX=17 (ESP32 RX→MH-Z19 TX) |
| MH-Z19 (old) | RX=14, TX=13 |
| TM1637 | DIO=33, CLK=32 |
| KY-016 RGB | R=5, G=18, B=19 |
| WS2812 ring | DIN=15 (via 300Ω) |

## Other Sketches

- `0_arduino_code_mqtt_display/` — T-ESP32-6, subscribes `tele/tasmota_MT681/SENSOR`, parses JSON `Power_cur`, 40MHz underclock
- `0_MH-Z19-Tools/` — MH-Z19 recovery & device info
