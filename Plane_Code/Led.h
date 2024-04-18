#include <FastLED.h>
//Led Pin
#define DATA_PIN 6
#define NUM_LEDS 8
#define Brigtnes 50

int frec = 1000;
uint8_t frec_counter = 0;
long long tmr = 0;
long long tmr2 = 0;
long long tmr3 = 0;
int hue = 0;
int8_t mult = 1;

long counter = 0;
bool state = true;
bool flash = false;
int type = 0;


CRGB leds[NUM_LEDS];
void LedSetup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.clear();
  FastLED.setBrightness(Brigtnes);  // ограничить максимальную яркость
}
//0-norm, 1-alarm, 2 - error
void doLight() {
  Serial.println(frec);
  if (millis() - tmr >= frec) {
    state = !state;
    frec_counter++;
    if (frec >= 700) {
      frec = 200;
    } else if (frec <= 700 && frec_counter == 4) {
      frec = 1800;
      frec_counter = 0;
    }
    tmr = millis();
  }
  if (millis() - tmr2 >= 5) {
    leds[4] = CRGB::White;
    leds[5] = CRGB(255, 255, 100);
    leds[6] = CRGB::White;
    leds[7] = CRGB(255, 255, 100);

    tmr2 = millis();
  }
  if (millis() - tmr3 >= 40) {
    hue += mult;
    if (hue >= 250) {
      hue = 250;
      mult = -10;
    }
    if (hue == 20) {
      hue = 20;
      mult = 10;
    }
    tmr3 = millis();
  }
  if (state) {
    leds[0] = CRGB::Red;
    leds[1] = CRGB::White;
    leds[2] = CRGB::Green;
  }
  if (!state) {
    leds[0] = CRGB::White;
    leds[1] = CRGB::White;
    leds[2] = CRGB::White;
  }
  leds[3] = CRGB(hue, 0, 0);
  FastLED.show();
}
