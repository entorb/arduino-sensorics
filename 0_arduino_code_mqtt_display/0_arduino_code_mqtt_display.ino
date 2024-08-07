#include <Arduino.h>

#include "esp32-hal-cpu.h" // for power saving via setCpuFrequencyMhz()

// WiFi
#include <WiFi.h>
#include "TM_WiFi_secret.h" // file holding my WiFi credentials
#include "esp_wifi.h"       // for power saving via esp_wifi_set_ps()

// MQTT
// from https://www.emqx.com/en/blog/esp32-connects-to-the-free-public-mqtt-broker
#include "TM_MQTT_secret.h" // file holding my MQTT credentials
#include <PubSubClient.h>

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

  // WiFi
  wifi_connect();
  // enable Power Saving Modem
  esp_wifi_set_ps(WIFI_PS_MAX_MODEM);

  // MQTT
  mqtt_connect();
  mqtt_client.subscribe("tele/tasmota_MT681/SENSOR");
  // mqtt_client.publish("esp32/test", "ESP32 body");

  // Display
  my_display.setBrightness(4, true);
  my_display.clear();
}

void loop()
{
  mqtt_client.loop();
}

void wifi_connect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE); // required to set hostname properly
  WiFi.setHostname(my_device_name);
  int i = 0;
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    if (i == 15)
    {
      WiFi.reconnect();
      i = 0;
    }
    Serial.print(".");
    delay(500);
    i++;
  }
  Serial.println();
}

void mqtt_connect()
{
  mqtt_client.setServer(MQTT_HOST, MQTT_PORT);
  mqtt_client.setCallback(mqtt_callback_message_processor);
  while (!mqtt_client.connected())
  {
    Serial.printf("Connecting to MQTT broker as %s\n", my_device_name);
    if (mqtt_client.connect(my_device_name, MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("MQTT broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(mqtt_client.state());
      delay(2000);
    }
  }
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

  Serial.print(powerCurInt);
  Serial.println("W");
  my_display.showNumberDec(powerCurInt, false);
}
