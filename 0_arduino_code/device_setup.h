//
// setup this device
//

// Debugging
static const int mySleep = 2 * 1000;
static const bool myVerbose = true;

// Normal Mode
// static const int mySleep = 60 * 1000;
// static const bool myVerbose = false;

// Devices to load
// #define TM_LOAD_DEVICE_INFLUXDB
#define TM_LOAD_DEVICE_BME280
#define TM_LOAD_DEVICE_MHZ19
// #define TM_LOAD_DEVICE_OLED_128X32
#define TM_LOAD_DEVICE_OLED_128X64
#define TM_LOAD_DEVICE_LED_RING
#define TM_LOAD_DEVICE_LED_KY_016
#define TM_LOAD_DEVICE_7_SEGMENT
// EPS32 Setup
static const char my_device_name[] = "T-ESP32-4";
static const char my_room[] = "Arbeitszimmer";

/*
  Arbeitszimmer
  Kind 1
  Kind 2
  Bad
  Wintergarten
*/
