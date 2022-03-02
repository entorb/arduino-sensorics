// General
static const char my_device_name[] = "T-ESP32-1";
static const char my_room[] = "Arbeitszimmer";

// do not use a  value > 15s as otherwise flashing becomes difficult
static const int mySleep = 5 * 1000; // = duration of loop
static const bool myVerbose = true;

// Upload to Influx DB and clock settings
#define TM_LOAD_DEVICE_INFLUXDB
#define TM_DISPLAY_TIME
#define TM_HOUR_SLEEP 21
#define TM_HOUR_WAKE 6

// Sensors
#define TM_LOAD_DEVICE_BME280
// #define TM_LOAD_DEVICE_BH1750
// #define TM_LOAD_DEVICE_BME680
#define TM_LOAD_DEVICE_MHZ19
#define TM_MHZ19_PIN_RX 16
#define TM_MHZ19_PIN_TX 17

// Displays
#define TM_LOAD_DEVICE_4_DIGIT
#define TM_LOAD_DEVICE_LED_KY_016
// #define TM_LOAD_DEVICE_OLED_128X64
// #define TM_LOAD_DEVICE_OLED_128X32
// #define TM_LOAD_DEVICE_LED_RING
