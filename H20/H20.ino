#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 17
// #define NUM_STRIPS 5
// CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

CRGB wing1[NUM_LEDS_PER_STRIP];
CRGB wing2[NUM_LEDS_PER_STRIP];
CRGB wing3[NUM_LEDS_PER_STRIP];
CRGB wing4[NUM_LEDS_PER_STRIP];
CRGB wing5[NUM_LEDS_PER_STRIP];
CRGB wing6[NUM_LEDS_PER_STRIP];

#define BRIGHTNESS          255

// MOONBASE PARTS

int WING2_INNER[8] = {18, 19, 20, 21, 22, 23, 24, 25};
int WING2_OUTER[8] = {26, 27, 28, 29, 30, 31, 32, 33};

int WING3_INNER[8] = {35, 36, 37, 38, 39, 40, 41, 42};
int WING3_OUTER[8] = {43, 44, 45, 46, 47, 48, 49, 50};

int WING4_INNER[8] = {52, 53, 54, 55, 56, 57, 58, 59};
int WING4_OUTER[8] = {60, 61, 62, 63, 64, 65, 66, 67};

int WING5_INNER[8] = {69, 70, 71, 72, 73, 74, 75, 76};


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  delayMicroseconds(1000); // 3 second delayMicroseconds for recovery
  Serial.begin(9600);
  Serial.println("Serial connected!");

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<OCTOWS2811>(wing1, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<OCTOWS2811>(wing2, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<OCTOWS2811>(wing3, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<OCTOWS2811>(wing5, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<OCTOWS2811>(wing6, NUM_LEDS_PER_STRIP);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    // leds[i] =  CRGB::Black;
    wing1[i] = CRGB::Black;
    wing2[i] = CRGB::Black;
    wing3[i] = CRGB::Black;
    wing5[i] = CRGB::Black;
    wing6[i] = CRGB::Black;
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
  // print the string when a newline arrives:
  //  int blendFactor = 51;
  switch (serialInputPatternMode) {
    case 1:
    spiralInRainbow();
    break;
    case 2:
    spiralOutRainbow();
    break;
    default:
    spiralInRainbow();
    break;
  }
}
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
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      wing1[i] = CHSV(h, s, v);
      FastLED.show();
      delayMicroseconds(spinSpeed);
      wing2[i] = CHSV(h + blendFactor, s, v);
      FastLED.show();
      delayMicroseconds(spinSpeed);
      wing3[i] = CHSV(h + blendFactor * 2, s, v);
      FastLED.show();
      delayMicroseconds(spinSpeed);
      wing5[i] = CHSV(h + blendFactor * 3, s, v);
      FastLED.show();
      delayMicroseconds(spinSpeed);
      wing6[i] = CHSV(h + blendFactor * 4, s, v);
      FastLED.show();
      delayMicroseconds(spinSpeed);
    }
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

void spiralMoonbaseIn(int h, int s, int v, int delayMicrosecondsTime) {
  CHSV color( h, s, v);
  // Spiral in
  for(int i = NUM_LEDS_PER_STRIP - 1; i > -1; i--) {
    wing1[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing2[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing3[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing5[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing6[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
  }
}

void spiralMoonbaseOut(int h, int s, int v, int delayMicrosecondsTime) {
  CHSV color( h, s, v);
  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    wing1[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing2[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing3[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing5[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
    wing6[i] = color;
    FastLED.show();
    delayMicroseconds(delayMicrosecondsTime);
  }
}

