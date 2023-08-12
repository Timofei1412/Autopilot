#include <FastLED.h>
//Led Pin
#define DATA_PIN 6

#define NUM_LEDS 8
#define frec 1000
#define Brigtnes 250

long long tmr = 0;
long long tmr2 = 0;
long long tmr3 = 0;
int hue = 0;
int8_t mult = 1;

long counter = 0;
bool state = true;

CRGB leds[NUM_LEDS];
void LedSetup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.clear();
  FastLED.setBrightness(Brigtnes);  // ограничить максимальную яркость
}
void doLIght() {
  if (millis() - tmr >= frec) {
    state = !state;
    tmr = millis();
  }
  if (millis() - tmr2 >= 5) {
    leds[4] = CRGB::White;
    leds[5] = CRGB(255, 255, 100);
    leds[6] = CRGB::White;
    leds[7] = CRGB(255, 255, 100);

    tmr2 = millis();
  }

  if (millis() - tmr3 >= 12) {
    hue += mult;
    if (hue >= 250) {
      hue = 250;
      mult = -10;
    }
    if (hue <= 10) {
      hue = 10;
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
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
  }
  leds[3] = CRGB(hue, 0, 0);
  FastLED.show();
}

void alarm(int timer) {
  int m = millis();
  while (millis - m < timer) {
    FastLED.clear();
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::OrangeRed;
    }
    FastLED.show();
    fly();
  }
  doLIght();
}