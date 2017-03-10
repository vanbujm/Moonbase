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
#define FRAMES_PER_SECOND  120


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
boolean flipFlop = true;

void setup() {
  delay(1000); // 3 second delay for recovery
  Serial.begin(115200);
  Serial.println("Serial connected!");
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] =  CRGB::Black;
    FastLED.show();
  }
}


//// List of patterns to cycle through.  Each is defined as a separate function below.
//typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
//
//uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
//uint8_t gHue = 0; // rotating "base color" used by many of the patterns

int serialIntInput = FRAMES_PER_SECOND;
String inString = "";

void loop() {
  int blendFactor = 51;
  serialInput();
  //  pinwheelMoonbase(200, 255, blendFactor, serialIntInput);
  spiralInMoonbaseRainbow(serialIntInput);
}

void serialInput() {
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      boolean isString =  true;
      if (isValidNumber(inString)) {
        serialIntInput = inString.toInt();
      }
      Serial.print("String: ");
      Serial.println(inString);
      // clear the string for new input:
      inString = "";
    }
  }
}

boolean isValidNumber(String str) {
  for (byte i = 0; i < str.length(); i++)
  {
    if (isDigit(str.charAt(i))) return true;
  }
  return false;
}

void pinwheelMoonbase(int s, int v, int blendFactor, int spinSpeed) {
  for (int h = 0; h < 255; h += blendFactor) {
    for (int i = 0; i < 8; i++) {
      leds[WING5_OUTER[i]] = CHSV(h, s, v);

      leds[WING4_OUTER[i]] = CHSV(h + blendFactor, s, v);

      leds[WING3_OUTER[i]] = CHSV(h + blendFactor * 2, s, v);

      leds[WING2_OUTER[i]] = CHSV(h + blendFactor * 3, s, v);

      leds[WING1_OUTER[i]] = CHSV(h + blendFactor * 4, s, v);

      leds[WING5_INNER[i]] = CHSV(h, s, v);

      leds[WING4_INNER[i]] = CHSV(h + blendFactor, s, v);

      leds[WING3_INNER[i]] = CHSV(h + blendFactor * 2, s, v);

      leds[WING2_INNER[i]] = CHSV(h + blendFactor * 3, s, v);

      leds[WING1_INNER[i]] = CHSV(h + blendFactor * 4, s, v);
    }
    leds[CENTER[4]] = CHSV(h, s, v);
    leds[CENTER[3]] = CHSV(h + blendFactor, s, v);
    leds[CENTER[2]] = CHSV(h + blendFactor * 2, s, v);
    leds[CENTER[1]] = CHSV(h + blendFactor * 3, s, v);
    leds[CENTER[0]] = CHSV(h + blendFactor * 4, s, v);
    FastLED.show();
    FastLED.delay(spinSpeed);
  }
}

void spiralInMoonbaseRainbow(int spiralSpeed) {
  for (int h; h < 255; h += spiralSpeed) {
    spiralMoonbaseIn(h, 200, 255);
  }
}

void spiralMoonbaseIn(int h, int s, int v) {
  CHSV color( h, s, v);
  // Spiral in
  for (int i = 7; i > -1; i--) {
    leds[WING5_OUTER[i]] = color;
    leds[WING4_OUTER[i]] = color;
    leds[WING3_OUTER[i]] = color;
    leds[WING2_OUTER[i]] = color;
    leds[WING1_OUTER[i]] = color;
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND / 3);
  }
  for (int i = 7; i > -1; i--) {
    leds[WING5_INNER[i]] = color;
    leds[WING4_INNER[i]] = color;
    leds[WING3_INNER[i]] = color;
    leds[WING2_INNER[i]] = color;
    leds[WING1_INNER[i]] = color;
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND / 3);
  }

  for (int i = 5; i > -1; i--) {
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
  }
  FastLED.show();
}

void spiralMoonbaseOut(int h, int s, int v) {
  CHSV color( h, s, v);
  // Spiral in
  for (int i = 0; i < 5; i++) {
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
    leds[CENTER[i]] = color;
  }
  FastLED.show();

  for (int i = 0; i < 8; i++) {
    leds[WING5_INNER[i]] = color;
    leds[WING4_INNER[i]] = color;
    leds[WING3_INNER[i]] = color;
    leds[WING2_INNER[i]] = color;
    leds[WING1_INNER[i]] = color;
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND / 3);
  }

  for (int i = 0; i < 8; i++) {
    leds[WING5_OUTER[i]] = color;
    leds[WING4_OUTER[i]] = color;
    leds[WING3_OUTER[i]] = color;
    leds[WING2_OUTER[i]] = color;
    leds[WING1_OUTER[i]] = color;
    FastLED.show();
    FastLED.delay(1000 / FRAMES_PER_SECOND / 3);
  }

}

