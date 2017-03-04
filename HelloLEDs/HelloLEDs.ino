#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    85
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          255
//#define FRAMES_PER_SECOND  120


// MOONBASE PARTS
int CENTER[5] = {0, 17, 34, 51, 68};

int WING1_INNER[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int WING1_OUTER[8] = {9, 10, 11, 12, 13, 14, 15, 16};

int WING2_INNER[8] = {18, 19, 20, 21, 22, 23, 24, 25};
int WING2_OUTER[8] = {26, 27, 28, 29, 30, 31, 32, 33};

int WING3_INNER[8] = {35, 36, 37, 38, 39, 40, 41, 42};
int WING3_OUTER[8] = {43, 44, 45, 46, 47, 48, 49, 50};

int WING4_INNER[8] = {52, 53, 54, 55, 56, 57, 58, 59};
int WING4_OUTER[8] = {60, 61, 62, 63, 64, 65, 66, 67};

int WING5_INNER[8] = {69, 70, 71, 72, 73, 74, 75, 76};
int WING5_OUTER[8] = {77, 78, 79, 80, 81, 82, 83, 84};

void setup() {
  delay(1000); // 3 second delay for recovery
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] =  CRGB::Black;
  }
}


//// List of patterns to cycle through.  Each is defined as a separate function below.
//typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
//
//uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
//uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop() {
  //  for (int r = 0; r < 255; r += 50 ) {
  //    for (int g = 0; g < 255; g += 50) {
  for (int h = 0; h < 255; h += 50) {
    spiralMoonbaseIn(h, 255, 255, 10000);
    //      }
    //    }
  }
}

void spiralMoonbaseIn(int h, int s, int v, int delayTime) {

  // Spiral in
  for (int i = 7; i > -1; i--) {
    leds[WING5_OUTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING4_OUTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING3_OUTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING2_OUTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING1_OUTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
  }
  for (int i = 7; i > -1; i--) {
    leds[WING5_INNER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING4_INNER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING3_INNER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING2_INNER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING1_INNER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
  }

  for (int i = 5; i > -1; i--) {
    leds[CENTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV( h, s, v);
    FastLED.show();
    delayMicroseconds(delayTime);
  }
}

void spiralMoonbaseOut(int r, int g, int b, int delayTime) {
  for (int i = 0; i < 5; i++) {
    leds[CENTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = CHSV(r, g, b);
    delayMicroseconds(delayTime);
  }

  for (int i = 0; i < 8; i++) {
    leds[WING5_INNER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING4_INNER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING3_INNER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING2_INNER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING1_INNER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
  }
  for (int i = 0; i < 8; i++) {
    leds[WING5_OUTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING4_OUTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING3_OUTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING2_OUTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
    leds[WING1_OUTER[i]] = CHSV(r, g, b);
    FastLED.show();
    delayMicroseconds(delayTime);
  }
}

void pulseLEDArray(int sectionArray[], int arraySize, boolean scaleUp, int pulseFactor) {
  for (int i = 0 ; i < arraySize; i++) {
    if (!scaleUp) {
      leds[sectionArray[i]].r -= pulseFactor;
    }
    else {
      leds[sectionArray[i]].r += pulseFactor;
    }
  }
}

//
//void nextPattern()
//{
//  // add one to the current pattern number, and wrap around at the end
//  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
//}
//
//void rainbow()
//{
//  // FastLED's built-in rainbow generator
//  fill_rainbow( leds, NUM_LEDS, gHue, 7);
//}
//
//void rainbowWithGlitter()
//{
//  // built-in FastLED rainbow, plus some random sparkly glitter
//  rainbow();
//  addGlitter(80);
//}
//
//void addGlitter( fract8 chanceOfGlitter)
//{
//  if( random8() < chanceOfGlitter) {
//    leds[ random16(NUM_LEDS) ] += CHSV::White;
//  }
//}
//
//void confetti()
//{
//  // random colored speckles that blink in and fade smoothly
//  fadeToBlackBy( leds, NUM_LEDS, 10);
//  int pos = random16(NUM_LEDS);
//  leds[pos] += CHSV( gHue + random8(64), 200, 255);
//}
//
//void sinelon()
//{
//  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16(13,0,NUM_LEDS);
//  leds[pos] += CHSV( gHue, 255, 192);
//}
//
//void bpm()
//{
//  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
//  uint8_t BeatsPerMinute = 62;
//  CHSVPalette16 palette = PartyColors_p;
//  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
//  for( int i = 0; i < NUM_LEDS; i++) { //9948
//    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
//  }
//}
//
//void juggle() {
//  // eight colored dots, weaving in and out of sync with each other
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  byte dothue = 0;
//  for( int i = 0; i < 8; i++) {
//    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
//    dothue += 32;
//  }
//}

