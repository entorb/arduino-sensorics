//
// setup this device
//

static const int mySleep = 60 * 1000; // milli sec
// deprecated, because not available in classes: #define TM_VERBOSE 1 // 0 disables all Serial.print() calls
static const bool myVerbose = false;
#define TM_LOAD_DEVICE_INFLUXDB 1
#define TM_LOAD_DEVICE_BME280 0
#define TM_LOAD_DEVICE_MHZ19 1
#define TM_LOAD_DEVICE_OLED_128X32 0
#define TM_LOAD_DEVICE_OLED_128X64 1
static const char my_device_name[] = "T-ESP32-1";
static const char my_room[] = "Arbeitszimmer";
/*
  Arbeitszimmer
  Kind 1
  Kind 2
  Bad
  Wintergarten
*/
