/*
  TM_LED_Ring_Class.cpp - Library for powering WS2812 LED Ring
  */

/*
from https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/AnalogOut/LEDCSoftwareFade/LEDCSoftwareFade.ino
 LEDC Software Fade
 This example shows how to software fade LED
 using the ledcWrite function.
 Code adapted from original Arduino Fade example:
 https://www.arduino.cc/en/Tutorial/Fade
 This example code is in the public domain.
 */

// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0 0

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT 13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ 5000

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define LED_PIN 12

#include "TM_Device_Class.h"
#include "TM_LED_KY_016_Class.h"

#include "Arduino.h" // for Serial.println()

TM_LED_KY_016_Class::TM_LED_KY_016_Class() : TM_Device_Class()
{
  // Setup timer and attach timer to a led pin
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED_PIN, LEDC_CHANNEL_0);
}

// Arduino like analogWrite
// value has to be between 0 and valueMax
void TM_LED_KY_016_Class::ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255)
{
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}

void TM_LED_KY_016_Class::fadeIn_fadeOut()
{
  // set the brightness on LEDC channel 0
  ledcAnalogWrite(LEDC_CHANNEL_0, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255)
  {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}