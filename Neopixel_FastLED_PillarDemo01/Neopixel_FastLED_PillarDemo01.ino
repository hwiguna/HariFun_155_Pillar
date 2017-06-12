#include "FastLED.h"

#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
int ledBrightness[NUM_LEDS];
CRGB colors[4];

#define DATA_PIN 3
const int pace = 500;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  colors[0] = CRGB::Red;
  colors[1] = CRGB::Green;
  colors[2] = CRGB::Blue;
  colors[3] = CRGB::White;

  FastLED.setBrightness(255);
}

void SetLedBrightness(int which, int r, int g, int b, int brightness)
{
  ledBrightness[which] = brightness;
  leds[which].setRGB(r * brightness / 255, g * brightness / 255, b * brightness / 255);
}

void GradualRise()
{
  //-- Turn them all off --
  for (int i = 0; i < NUM_LEDS; i++)
    SetLedBrightness(i, 0, 0, 0, 0);
  FastLED.show();

  int brightnessDelay = 100; // Larger = slower
  int risePace = 8;
  int brightness = 0;
  int nextBrightness = 0; // When brightness reach this value, it's time to turn on the next LED
  int brightnessThreshold = 255 / NUM_LEDS; // How much brightness would have to change before we turn on next LED
  int currentTop = 0; // Topmost led that is currently on
  bool done = false;
  while (!done)
  {
    // Make leds from bottom to current topmost a little brighter
    for (int i = 0; i <= currentTop; i++)
    {
      if (ledBrightness[i] < 255)
        ledBrightness[i]++;
      SetLedBrightness(i, 255, 255, 255, ledBrightness[i]);
    }

    // When we've increased brightness enough, include the next higher LED.
    if (ledBrightness[0] >= nextBrightness) {
      nextBrightness = ledBrightness[0] + brightnessThreshold;
      if (currentTop < (NUM_LEDS - 1)) currentTop++;
    }

    if (ledBrightness[NUM_LEDS - 1] >= 255) {
      done = true;
    }
    FastLED.delay(7);
  }
}

void Fall()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    SetLedBrightness(NUM_LEDS - 1 - i, 0, 0, 0, 0);
    FastLED.delay(100);
  }
}

void Rise(int r, int g, int b)
{
  for (int i = 0; i < NUM_LEDS; i++) {
    SetLedBrightness(i, r, g, b, 255);
    FastLED.delay(100);
  }
}

void ColorTests()
{
  for (int c = 0; c < 4; c++)
  {
    int cr = 0, cg = 0, cb = 0;
    switch (c) {
      case 0: cr = 255; break;
      case 1: cg = 255; break;
      case 2: cb = 255; break;
      case 3: cr = cg = cb = 255; break;
    }
    Rise(cr, cg, cb);
    delay(2000); // Enjoy the glory for two seconds before repeating

    Fall();
    delay(1000); // Enjoy the silence
  }
}

void DripDrip()
{
  for (int r = 0; r < 3; r++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      int y = NUM_LEDS - 1 - i;
      leds[y] = CRGB::White;
      FastLED.delay(80);
      leds[y] = CRGB::Black;
      FastLED.show();
    }
    delay(500);
  }
}

void SetAll(CRGB c)
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = c;
    FastLED.show();
  }
}

void Blink()
{
  SetAll(CRGB::White);
  FastLED.delay(1000);
  SetAll(CRGB::Black);
  FastLED.delay(1000);
}
void loop() {
  //-- Demo 1 --
  Blink();

  //-- Demo 2 --
//  DripDrip();

  //-- Demo 3 --
//    ColorTests();
//  
//    GradualRise();
//    delay(1000); // Enjoy the silence
//  
//    Fall();
//    delay(2000); // Enjoy the silence
}

