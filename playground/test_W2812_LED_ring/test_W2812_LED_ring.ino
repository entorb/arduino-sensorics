#include <Adafruit_NeoPixel.h>

#define PIN 15
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


uint32_t color[8] = {
  0x00ff00, // green
  0x19e600,
  0x95fc00,
  0xffff00, // yellow
  0xff8700,
  0xcc3300,
  0xe61a00,
  0xff0000  // red
};

void setup()
{
  pixels.begin();
  pixels.setBrightness(32);
}

int loopNum = 0;
void loop()
{
  pixels.clear(); // Set all pixel colors to 'off'
  // Loop over brightness
  // pixels.setBrightness(loopNum*32);

  /*
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 31, 0)); // 0..255
      pixels.show();
      delay(DELAYVAL); // Pause before next pass through loop
    }
  */

  for (int i = 0; i <= loopNum; i++)
  {
    pixels.setPixelColor(i, color[i]);
  }
  pixels.show();
  loopNum++;
  if (loopNum > 7)
    loopNum = 0;
  delay(500);
}
