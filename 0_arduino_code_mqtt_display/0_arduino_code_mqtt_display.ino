#include <Arduino.h>

#include "esp32-hal-cpu.h" // for power saving via setCpuFrequencyMhz()

// WiFi
#include <WiFi.h>
#include "esp_wifi.h"       // for power saving via esp_wifi_set_ps()
#include "TM_WiFi_secret.h" // WiFi credentials

// MQTT
// from https://www.emqx.com/en/blog/esp32-connects-to-the-free-public-mqtt-broker
#include <PubSubClient.h>
#include "TM_MQTT_secret.h" // MQTT credentials

// Display
#include <TM1637Display.h>

// Variables
static const char my_device_name[] = "T-ESP32-6";
WiFiClient espWiFiClient;
PubSubClient mqtt_client(espWiFiClient);
TM1637Display my_display(32, 33); // pin_clk, pin_dio

void setup()
{
  Serial.begin(115200);

  // ESP32
  setCpuFrequencyMhz(80); // 240, 160, 80

  // Display
  my_display.clear();
  my_display.setBrightness(0, true);
  my_display.showNumberDec(0, true);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    wifi_connect();
  }

  if (!mqtt_client.connected())
  {
    mqtt_connect();
  }

  mqtt_client.loop();
}

void wifi_connect()
{
  my_display.showNumberDec(100, true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); // required to set hostname properly
  WiFi.setHostname(my_device_name);
  int i = 0;
  Serial.printf("Connecting to WiFi as %s\n", my_device_name);
  while (WiFi.status() != WL_CONNECTED)
  {
    my_display.showNumberDec(101 + i, true);
    Serial.print(".");
    delay(1000);
    if (i == 15) // reconnect after 15s
    {
      WiFi.reconnect();
      i = 0;
    }
    i++;
  }
  // connection successful
  Serial.println(); // final linebreak after the "."
  my_display.showNumberDec(120, true);
  // enable Power Saving Modem
  esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
}

void mqtt_connect()
{
  my_display.showNumberDec(200, true);
  mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
  mqtt_client.setCallback(mqtt_callback_message_processor);
  Serial.printf("Connecting to MQTT as %s\n", my_device_name);
  int i = 0;
  while (!mqtt_client.connected())
  {
    my_display.showNumberDec(201 + i, true);
    if (!mqtt_client.connect(my_device_name, MQTT_USER, MQTT_PASSWORD))
    {
      Serial.printf("Failed with state %d\n", mqtt_client.state());
      delay(1000 * (i + 1));
    }
    if (i == 15) // restart after 15 retries
    {
      ESP.restart();
    }
    i++;
  }
  // connection successful
  my_display.showNumberDec(220, true);
  mqtt_client.subscribe("tele/tasmota_MT681/SENSOR");
  // mqtt_client.publish("esp32/test", "ESP32 body");
}

void mqtt_callback_message_processor(char *topic, byte *payload, unsigned int length)
{
  // example payload
  // {"Time":"2024-08-07T08:53:42","MT681":{"Total_in":186.7106,"Power_cur":79.9,"Total_out":266.8507}}
  String payloadString = "";
  for (int i = 0; i < length; i++)

  {
    // Serial.print((char)payload[i]);
    payloadString += (char)payload[i];
  }
  // Serial.println();

  // Extract the "Power_cur" value
  String key = "\"Power_cur\":";
  int startIndex = payloadString.indexOf(key) + key.length();
  int endIndex = payloadString.indexOf(",", startIndex);
  String powerCurString = payloadString.substring(startIndex, endIndex);
  int powerCurInt = (int)(powerCurString.toFloat());

  my_display.showNumberDec(powerCurInt, false);
  Serial.printf("%dW\n", powerCurInt);
}
