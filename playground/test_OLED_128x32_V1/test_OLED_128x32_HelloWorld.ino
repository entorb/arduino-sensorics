
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

char* text = "Mojnsen";
/*
int text_length = (str(text)).length(); // 7
int font_width = 16;
// 7 * 16  = 112
int font_height = 19;
int display_px_x = 128;
int display_px_y = 32;
// (display_px_y - font_height) = 13
*/



void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_inb19_mf);  // https://github.com/olikraus/u8g2/wiki/fntlistall
  // u8g2_font_inb19_mf: bbox = 16, max height = 31
  // u8g2.setFontRefHeightExtendedText(); //https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontrefheightextendedtext
  u8g2.setFontPosTop(); // setFontPosTop() , setFontPosBaseline() , setFontPosCenter() , setFontPosBottom()
  u8g2.setFontDirection(0); // 0..3

}

int x_offset = 0;
void loop() {
  u8g2.clearBuffer();
  // x, y, str
  u8g2.drawStr(x_offset,7, text);
  u8g2.sendBuffer();
  delay(1000);
  if (x_offset <= 16) {
    x_offset++;
  } else {
    x_offset = 0;
  }
}
