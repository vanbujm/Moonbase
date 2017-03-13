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
#define NUM_LEDS    89
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




// H20 PARTS HeightMap
int H20_HEIGHT_MAP_ROW_1_SIZE = 7;
int H20_HEIGHT_MAP_ROW_1[7] = {48, 49, 50, 51, 52, 53, 54};
int H20_HEIGHT_MAP_ROW_2_SIZE = 1;
int H20_HEIGHT_MAP_ROW_2[1] = {47};
int H20_HEIGHT_MAP_ROW_3_SIZE = 1;
int H20_HEIGHT_MAP_ROW_3[1] = {46};
int H20_HEIGHT_MAP_ROW_4_SIZE = 1;
int H20_HEIGHT_MAP_ROW_4[1] = {45};
int H20_HEIGHT_MAP_ROW_5_SIZE = 1;
int H20_HEIGHT_MAP_ROW_5[1] = {44};
int H20_HEIGHT_MAP_ROW_6_SIZE = 7;
int H20_HEIGHT_MAP_ROW_6[7] = {12, 32, 43, 75, 74, 73, 72};


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  delay(1000); // 3 second delay for recovery
  Serial.begin(9600);
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

String inString = "";
boolean flipFlop = true;
int pinwheelOffset = 0;

int serialInputSpiralSpeed = 15;
int serialInputColorJump = 17;
int serialInputSaturation = 255;
int serialInputBrightness = 255;

int serialInputPatternMode = 1;

char serialFlag = '!';

void loop() {

  for (int i = 0; i < H20_HEIGHT_MAP_ROW_1_SIZE; i++) {
    leds[H20_HEIGHT_MAP_ROW_1[i]] = CHSV(255, 255, 255);
  }

  for (int i = 0; i < H20_HEIGHT_MAP_ROW_2_SIZE; i++) {
    leds[H20_HEIGHT_MAP_ROW_2[i]] = CHSV(255, 255, 255);
  }

  for (int i = 0; i < H20_HEIGHT_MAP_ROW_3_SIZE; i++) {
    leds[H20_HEIGHT_MAP_ROW_3[i]] = CHSV(255, 255, 255);
  }

  for (int i = 0; i < H20_HEIGHT_MAP_ROW_4_SIZE; i++) {
    leds[H20_HEIGHT_MAP_ROW_4[i]] = CHSV(255, 255, 255);
  }

  for (int i = 0; i < H20_HEIGHT_MAP_ROW_5_SIZE; i++) {
    leds[H20_HEIGHT_MAP_ROW_5[i]] = CHSV(255, 255, 255);
  }

  for (int i = 0; i < H20_HEIGHT_MAP_ROW_6_SIZE; i++) {
    leds[H20_HEIGHT_MAP_ROW_6[i]] = CHSV(255, 255, 255);
  }

  FastLED.show();
}


/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    boolean shouldClear = false;
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '!') {
      serialFlag = '!';
      assignSerial();
      shouldClear = true;
    }
    if (inChar == '@') {
      serialFlag = '@';
      assignSerial();
      shouldClear = true;
    }
    if (inChar == '#') {
      serialFlag = '#';
      assignSerial();
      shouldClear = true;
    }
    if (inChar == '$') {
      serialFlag = '$';
      assignSerial();
      shouldClear = true;
    }
    if (inChar == '%') {
      serialFlag = '%';
      assignSerial();
      shouldClear = true;
    }
    if (shouldClear) {
      inputString = "";
    }
  }
}

void assignSerial() {
  Serial.println(inputString);
  if (isValidNumber(inputString)) {
    int number = inputString.toInt();
    if (serialFlag == '!') {
      serialInputColorJump =  number;
    }
    if (serialFlag == '@') {
      serialInputSpiralSpeed =  number;
    }
    if (serialFlag == '#') {
      serialInputSaturation =  number;
    }
    if (serialFlag == '$') {
      serialInputBrightness =  number;
    }
    if (serialFlag == '%') {
      serialInputPatternMode =  number;
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
  for (int h = pinwheelOffset; h < 255; h += blendFactor) {
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
    delay(spinSpeed);
  }
}

void spiralInRainbow() {
  for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
    spiralMoonbaseIn(h, serialInputSaturation, serialInputBrightness, serialInputSpiralSpeed);
    pinwheelOffset =  h + serialInputColorJump;
  }
  pinwheelOffset = pinwheelOffset - 255;
}

void spiralOutRainbow() {
  for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
    spiralMoonbaseOut(h, serialInputSaturation, serialInputBrightness, serialInputSpiralSpeed);
    pinwheelOffset =  h + serialInputColorJump;
  }
  pinwheelOffset = pinwheelOffset - 255;
}

void spiralMoonbaseIn(int h, int s, int v, int delayTime) {
  CHSV color( h, s, v);
  // Spiral in
  for (int i = 7; i > -1; i--) {
    leds[WING5_OUTER[i]] = color;
    leds[WING4_OUTER[i]] = color;
    leds[WING3_OUTER[i]] = color;
    leds[WING2_OUTER[i]] = color;
    leds[WING1_OUTER[i]] = color;
    FastLED.show();
    delay(delayTime);
  }
  for (int i = 7; i > -1; i--) {
    leds[WING5_INNER[i]] = color;
    leds[WING4_INNER[i]] = color;
    leds[WING3_INNER[i]] = color;
    leds[WING2_INNER[i]] = color;
    leds[WING1_INNER[i]] = color;
    FastLED.show();
    delay(delayTime);
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

void spiralMoonbaseOut(int h, int s, int v, int delayTime) {
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
    delay(delayTime);
  }

  for (int i = 0; i < 8; i++) {
    leds[WING5_OUTER[i]] = color;
    leds[WING4_OUTER[i]] = color;
    leds[WING3_OUTER[i]] = color;
    leds[WING2_OUTER[i]] = color;
    leds[WING1_OUTER[i]] = color;
    FastLED.show();
    delay(delayTime);
  }

}


