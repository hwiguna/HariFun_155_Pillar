#include "FastLED.h"

#define NUM_LEDS 20
CRGB leds[NUM_LEDS];
CRGB colors[3];

#define DATA_PIN 3
const int pace = 500;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  colors[0] = CRGB::Red;
  colors[1] = CRGB::Green;
  colors[2] = CRGB::Blue;
}

void All()
{
  for (int c = 0; c < 3; c++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = colors[c];
      FastLED.show();
    }
    delay(pace);
  }
}

void OneAtATime()
{i
  
}

void FlipFlop()
{
  leds[7] = CRGB::Blue;
  leds[8] = CRGB::White;
  FastLED.show();
  delay(pace);

  leds[7] = CRGB::White;
  leds[8] = CRGB::Blue;
  FastLED.show();
  delay(pace);
}

void loop() {
  All();
  //FlipFlop();
}

