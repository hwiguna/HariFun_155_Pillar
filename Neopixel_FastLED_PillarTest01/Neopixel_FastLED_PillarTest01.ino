#include "FastLED.h"

#define NUM_LEDS 512
CRGB leds[NUM_LEDS];
CRGB colors[4];
//int cube[8][8][8];

#define DATA_PIN 3
const int pace = 500;

int ToIndex(int x, int y, int z)
{
  return (x % 2) ? (x * 8) + (7 - y) + z * 64 : (x * 8) + y + z * 64;
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  colors[0] = CRGB::Red;
  colors[1] = CRGB::Green;
  colors[2] = CRGB::Blue;
  colors[3] = CRGB::White;

  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      for (int z = 0; z < 8; z++)
        leds[ToIndex(x, y, z)] = CRGB::Black;
}

void All()
{
  for (int c = 0; c < 4; c++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = colors[c];
    }
    FastLED.show();
    FastLED.delay(500);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.delay(500);
  }
}

void OneAtATime()
{

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

void FillBottomUp(CRGB c, int topY, int numRows)
{
  for (int y = 0; y < 8; y++) {
    //    DrawRows()
  }
}

void Bounce()
{
  //== Up ==
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 3; x++) {
      int i = x * 8 + y;
      leds[i] = CRGB::White;
    }
    FastLED.show();
    FastLED.delay(70);
    for (int x = 0; x < 3; x++) {
      int i = x * 8 + y;
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

  //== Down ==
  for (int y = 1; y < 7; y++) {
    for (int x = 0; x < 3; x++) {
      int i = x * 8 + 7 - y;
      leds[i] = CRGB::White;
    }
    FastLED.show();
    FastLED.delay(70);
    for (int x = 0 ; x < 3; x++) {
      int i = x * 8 + 7 - y;
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }
}

void LeftRightUp()
{
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      int i = ToIndex(x, y, 0);
      leds[i] = CRGB::White;
      FastLED.show();
      FastLED.delay(100);
      leds[i] = CRGB::Black;
      FastLED.show();
    }
  }
}
void UpThenRight()
{
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      int i = ToIndex(x, y, 0);
      leds[i] = CRGB::White;
      FastLED.show();
      FastLED.delay(100);
      leds[i] = CRGB::Black;
      FastLED.show();
    }
  }
}

void loop() {
  All();
  //FlipFlop();
  //Bounce();
  //LeftRightUp();
  //UpThenRight();
}

