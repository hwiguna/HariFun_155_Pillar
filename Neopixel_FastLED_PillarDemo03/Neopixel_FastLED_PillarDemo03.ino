#include "FastLED.h"

#define ZMAX 2
#define NUM_LEDS 128
CRGB leds[NUM_LEDS];
int ledBrightness[NUM_LEDS];
CRGB colors[4];

#define DATA_PIN 3
const int pace = 500;

int ToIndex(int x, int y, int z)
{
  return (x % 2) ? (x * 8) + (7 - y) + z * 64 : (x * 8) + y + z * 64;
}

void WaitForTouch()
{
  int v = 0;
  do {
    v = digitalRead(2);
    delay(50);
  } while (v == HIGH);
  delay(200);
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
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      for (int z = 0; z < ZMAX; z++) {
        int i = ToIndex(x, 7 - y, z);
        SetLedBrightness(i, 0, 0, 0, 0);
      }
    }
    FastLED.delay(100);
  }
}

void Rise(int r, int g, int b)
{
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      for (int z = 0; z < ZMAX; z++) {
        int i = ToIndex(x, y, 0);
        SetLedBrightness( ToIndex(x, y, z), r, g, b, 255);
      }
    }
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
    delay(1500); // Enjoy the glory for two seconds before repeating

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
  FastLED.delay(2000);
  SetAll(CRGB::Black);
  FastLED.delay(2000);
}

void Bounce()
{
  //== Up ==
  for (int y = 0; y < 8; y++) {
    SetPlane(y, CRGB::White);
    FastLED.show();
    FastLED.delay(70);
    SetPlane(y, CRGB::Black);
    FastLED.show();
  }

  //== Down ==
  for (int y = 1; y < 7; y++) {
    SetPlane(7 - y, CRGB::White);
    FastLED.show();
    FastLED.delay(70);
    SetPlane(7 - y, CRGB::Black);
    FastLED.show();
  }
}

void Constant(CRGB c)
{
  for (int z = 0; z < ZMAX; z++) {
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        leds[ ToIndex(x, y, z) ] = c;
      }
    }
  }
  FastLED.show();
}

float Distance(int x1, int y1, int x2, int y2)
{
  return sqrt( sq(x1 - x2) + sq(y1 - y2) );
}

void Rainbow()
{
  int rx = 7; int ry = 0;
  int gx = 7; int gy = 7;
  int bx = 0; int by = 0;
  int m = 255 / 9.9;
  for (int z = 0; z < ZMAX; z++) {
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        int rr = (Distance(rx, ry, x, y)) * m;
        int gg = (Distance(gx, gy, x, y)) * m;
        int bb = (Distance(bx, by, x, y)) * m;
        leds[ ToIndex(x, y, z) ].setRGB(rr, gg, bb);
      }
    }
  }
  FastLED.show();
}

void Rainbow2()
{
  int rx = 7; int ry = 0;
  int gx = 7; int gy = 7;
  int bx = 0; int by = analogRead(1) * 7 / 1023;
  int m = 255 / 9.9;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      int rr = Distance(rx, ry, x, y) * m;
      int gg = Distance(gx, gy, x, y) * m;
      int bb = Distance(bx, by, x, y) * m;
      leds[ ToIndex(x, y, 0) ].setRGB(rr, gg, bb);
    }
  }
  FastLED.show();
}

void Explode()
{
  for (int i = 0; i < 4; i++) {
    //leds[ ToIndex(x - i, y, 0) ] = CRGB::White;
  }
}

void SetPlane(int y, CRGB c)
{
  for (int z = 0; z < ZMAX; z++) {
    for (int x = 0; x < 8; x++) {
      leds[ ToIndex(x, y, z) ] = c;
    }
  }
}

void ClearAll()
{
  for (int y = 0; y < 8; y++)
    SetPlane(y, CRGB::Black);
  FastLED.show();
}

void FloatUp(CRGB c, int finalY)
{
  for (int i = 0; i < 3; i++) {
    for (int y = 0; y <= finalY - i; y++)
    {
      if ((y - 0) >= 0) SetPlane(y - 0, c);
      if ((y - 1) >= 0) SetPlane(y - 1, CRGB::Black);
      FastLED.show();
      FastLED.delay(150);
    }
  }
}

void July4()
{
  //  ClearAll();
  //  FloatUp(CRGB::Red, 7);
  //  FloatUp(CRGB::White, 4);
  //  FloatUp(CRGB::Blue, 2);
  SetPlane(0, CRGB::Red);
  SetPlane(1, CRGB::Red);
  SetPlane(2, CRGB::Red);
  SetPlane(3, CRGB::White);
  SetPlane(4, CRGB::White);
  SetPlane(5, CRGB::Blue);
  SetPlane(6, CRGB::Blue);
  SetPlane(7, CRGB::Blue);
  FastLED.show();
}

void setup() {
  pinMode(2, INPUT_PULLUP);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  colors[0] = CRGB::Red;
  colors[1] = CRGB::Green;
  colors[2] = CRGB::Blue;
  colors[3] = CRGB::White;

  FastLED.setBrightness(255);

  Rainbow(); WaitForTouch();
}

void loop() {
  //July4();  WaitForTouch();
  Constant(CRGB::Red); WaitForTouch();
  Constant(CRGB::Green); WaitForTouch();
  Constant(CRGB::Blue); WaitForTouch();
  Constant(CRGB::Black); WaitForTouch();

  Rise(255, 0, 0);  WaitForTouch();
  Fall();  WaitForTouch();

  Rise(0, 255, 0);  WaitForTouch();
  Fall();  WaitForTouch();

  Rise(0, 0, 255);  WaitForTouch();
  Fall();  WaitForTouch();

  for (byte i = 0; i < 4; i++) Bounce();
  Constant(CRGB::Black);
  WaitForTouch();

  Rainbow(); WaitForTouch();
}

