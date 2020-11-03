//
// setup this device
//

// Devices to load
//#define TM_LOAD_DEVICE_INFLUXDB
//#define TM_LOAD_DEVICE_BME280
#define TM_LOAD_DEVICE_MHZ19
//#define TM_LOAD_DEVICE_OLED_128X32
#define TM_LOAD_DEVICE_OLED_128X64
//#define TM_LOAD_LED_RING
// #define TM_LOAD_LED_KY_016
// EPS32 Setup
static const char my_device_name[] = "T-ESP32-4";
static const char my_room[] = "Arbeitszimmer";

// Debugging
static const int mySleep = 2 * 1000; // milli sec
static const bool myVerbose = true;
// deprecated, because not available in classes: #define TM_VERBOSE 1 // 0 disables all Serial.print() calls

/*
  Arbeitszimmer
  Kind 1
  Kind 2
  Bad
  Wintergarten
*/
