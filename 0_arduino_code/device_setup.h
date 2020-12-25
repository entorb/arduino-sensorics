//
// setup this device
//

// see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/log.html
#define LOG_LOCAL_LEVEL ESP_LOG_ERROR

// Normal Mode
static const int mySleep = 15 * 1000;
// static const int mySleep = 3 * 1000; // for BME680 in LP mode it must be 3s!
static const bool myVerbose = false;

// Debugging
// static const int mySleep = 2 * 1000;
// static const bool myVerbose = true;

//
// Devices to load
//
// #define TM_LOAD_DEVICE_INFLUXDB
// #define TM_HOUR_SLEEP 22
// #define TM_HOUR_WAKE 6
// #define TM_LOAD_DEVICE_BME280
// #define TM_LOAD_DEVICE_BME680
// #define TM_LOAD_DEVICE_BH1750

#define TM_LOAD_DEVICE_MHZ19
// Newer layout
#define TM_MHZ19_PIN_RX 16
#define TM_MHZ19_PIN_TX 17
// Old KiTa Layout
// #define TM_MHZ19_PIN_RX 14
// #define TM_MHZ19_PIN_TX 13

#define TM_LOAD_DEVICE_4_DIGIT
// #define TM_LOAD_DEVICE_OLED_128X32
#define TM_LOAD_DEVICE_OLED_128X64
#define TM_LOAD_DEVICE_LED_KY_016
// #define TM_LOAD_DEVICE_LED_RING

//
// EPS32 Setup
//
// static const char my_device_name[] = "T-ESP32-1"; static const char my_room[] = "Arbeitszimmer";
// static const char my_device_name[] = "T-ESP32-2"; static const char my_room[] = "Bad";
// static const char my_device_name[] = "T-ESP32-3"; static const char my_room[] = "Kind 1";
// static const char my_device_name[] = "T-ESP32-4"; static const char my_room[] = "Wohnzimmer";
// static const char my_device_name[] = "T-ESP32-5"; static const char my_room[] = "Wintergarten";
// static const char my_device_name[] = "T-ESP32-6"; static const char my_room[] = "Wohnzimmer Falls";

static const char my_device_name[] = "T-ESP32-x";
// static const char my_room[] = "ASGS-1A";
// static const char my_room[] = "KiTa";
static const char my_room[] = "Wohnzimmer Menkes";
