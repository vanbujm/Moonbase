#include <Arduino.h>
#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 126
#define NUM_STRIPS 7
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP + 126 + 113];


#define BRIGHTNESS          255

void initializeArray(int* arr, int startNumber, int size);
void inOutWords(CHSV color, int delayTime);
void outInWords(CHSV color, int delayTime);
void inverseTracer();
void colorWordsRGB(CRGB color);
void colorWordsHSV(CHSV color);
void clearRGB(CRGB color);
void clearHSV(CHSV color);
void spiralTracerIn(int h, int s, int v, int spiralSpeed);
void rainbowTracer();
void serialEvent();
void assignSerial();
boolean isValidNumber(String str);
void pinwheelMoonbase(int s, int v, int blendFactor, int spinSpeed);
void spiralInRainbow();
void spiralOutRainbow();
void spiralMoonbaseIn(CHSV color, int spiralSpeed);
void spiralMoonbaseOut(CHSV color, int spiralSpeed);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete



// MOONBASE PARTS
int CENTER[5] = {0, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP * 2, NUM_LEDS_PER_STRIP * 3, NUM_LEDS_PER_STRIP * 4};

int WING1_INNER[8] = {
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8
};
int WING1_OUTER[8] = {
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16
};
int WING2_INNER[8] = {
  1 + NUM_LEDS_PER_STRIP,
  2 + NUM_LEDS_PER_STRIP,
  3 + NUM_LEDS_PER_STRIP,
  4 + NUM_LEDS_PER_STRIP,
  5 + NUM_LEDS_PER_STRIP,
  6 + NUM_LEDS_PER_STRIP,
  7 + NUM_LEDS_PER_STRIP,
  8 + NUM_LEDS_PER_STRIP
};
int WING2_OUTER[8] = {
  9 + NUM_LEDS_PER_STRIP,
  10 + NUM_LEDS_PER_STRIP,
  11 + NUM_LEDS_PER_STRIP,
  12 + NUM_LEDS_PER_STRIP,
  13 + NUM_LEDS_PER_STRIP,
  14 + NUM_LEDS_PER_STRIP,
  15 + NUM_LEDS_PER_STRIP,
  16 + NUM_LEDS_PER_STRIP
};
int WING3_INNER[8] = {
  1 + NUM_LEDS_PER_STRIP * 2,
  2 + NUM_LEDS_PER_STRIP * 2,
  3 + NUM_LEDS_PER_STRIP * 2,
  4 + NUM_LEDS_PER_STRIP * 2,
  5 + NUM_LEDS_PER_STRIP * 2,
  6 + NUM_LEDS_PER_STRIP * 2,
  7 + NUM_LEDS_PER_STRIP * 2,
  8 + NUM_LEDS_PER_STRIP * 2
};
int WING3_OUTER[8] = {
  9 + NUM_LEDS_PER_STRIP * 2,
  10 + NUM_LEDS_PER_STRIP * 2,
  11 + NUM_LEDS_PER_STRIP * 2,
  12 + NUM_LEDS_PER_STRIP * 2,
  13 + NUM_LEDS_PER_STRIP * 2,
  14 + NUM_LEDS_PER_STRIP * 2,
  15 + NUM_LEDS_PER_STRIP * 2,
  16 + NUM_LEDS_PER_STRIP * 2
};
int WING4_INNER[8] = {
  1 + NUM_LEDS_PER_STRIP * 3,
  2 + NUM_LEDS_PER_STRIP * 3,
  3 + NUM_LEDS_PER_STRIP * 3,
  4 + NUM_LEDS_PER_STRIP * 3,
  5 + NUM_LEDS_PER_STRIP * 3,
  6 + NUM_LEDS_PER_STRIP * 3,
  7 + NUM_LEDS_PER_STRIP * 3,
  8 + NUM_LEDS_PER_STRIP * 3
};
int WING4_OUTER[8] = {
  9 + NUM_LEDS_PER_STRIP * 3,
  10 + NUM_LEDS_PER_STRIP * 3,
  11 + NUM_LEDS_PER_STRIP * 3,
  12 + NUM_LEDS_PER_STRIP * 3,
  13 + NUM_LEDS_PER_STRIP * 3,
  14 + NUM_LEDS_PER_STRIP * 3,
  15 + NUM_LEDS_PER_STRIP * 3,
  16 + NUM_LEDS_PER_STRIP * 3
};
int WING5_INNER[8] = {
  1 + NUM_LEDS_PER_STRIP * 4,
  2 + NUM_LEDS_PER_STRIP * 4,
  3 + NUM_LEDS_PER_STRIP * 4,
  4 + NUM_LEDS_PER_STRIP * 4,
  5 + NUM_LEDS_PER_STRIP * 4,
  6 + NUM_LEDS_PER_STRIP * 4,
  7 + NUM_LEDS_PER_STRIP * 4,
  8 + NUM_LEDS_PER_STRIP * 4
};
int WING5_OUTER[8] = {
  9 + NUM_LEDS_PER_STRIP * 4,
  10 + NUM_LEDS_PER_STRIP * 4,
  11 + NUM_LEDS_PER_STRIP * 4,
  12 + NUM_LEDS_PER_STRIP * 4,
  13 + NUM_LEDS_PER_STRIP * 4,
  14 + NUM_LEDS_PER_STRIP * 4,
  15 + NUM_LEDS_PER_STRIP * 4,
  16 + NUM_LEDS_PER_STRIP * 4
};

// MOON

int M[37];
int M_SIZE = 37;
int O1[28];
int O1_SIZE = 28;
int O2[28];
int O2_SIZE = 28;
int N[33];
int N_SIZE = 33;

//BASE
int B[31];
int B_SIZE = 31;
int A[29];
int A_SIZE = 29;
int S[25];
int S_SIZE = 25;
int E[28];
int E_SIZE = 28;

//MOONBASEWORDS
int MOONBASEWORDS[239];
int MOONBASEWORDS_SIZE = 239;

void initializeArray(int arr[], int startNumber, int size) {
  int number =  startNumber;
  for(int i = 0; i < size; i++) {
    arr[i] = number;
    number++;
  }
}

void setup() {
  initializeArray(M, NUM_LEDS_PER_STRIP * 5, 37);
  initializeArray(O1, NUM_LEDS_PER_STRIP * 5 + 37, 28);
  initializeArray(O2, NUM_LEDS_PER_STRIP * 5 + 37 + 28, 28);
  initializeArray(N, NUM_LEDS_PER_STRIP * 5 + 37 + 28 +28, 33);
  initializeArray(B, NUM_LEDS_PER_STRIP * 6, 31);
  initializeArray(A, NUM_LEDS_PER_STRIP * 6 + 31, 29);
  initializeArray(S, NUM_LEDS_PER_STRIP * 6 + 31 + 29, 25);
  initializeArray(E, NUM_LEDS_PER_STRIP * 6 + 31+ 29 + 25, 28);

  initializeArray(MOONBASEWORDS, NUM_LEDS_PER_STRIP * 5, 239);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  delayMicroseconds(1000); // 3 second delayMicroseconds for recovery
  Serial.begin(9600);

  // Serial1.begin(9600);
  // Serial1.println("Bluetooth Enabled");

  // tell LEDS about the LED strip configuration
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);

  // set master brightness control
  LEDS.setBrightness(BRIGHTNESS);
  clearRGB(CRGB::Red);
  LEDS.show();
}

String inString = "";
boolean flipFlop = true;
int pinwheelOffset = 0;

int serialInputSpiralSpeed = 1000;
int serialInputColorJump = 120;
int serialInputSaturation = 255;
int serialInputBrightness = 255;

int serialInputPatternModeLogo = 4;
int serialInputPatternModeWords = 1;

char serialFlag = '!';

void loop() {
  switch (serialInputPatternModeLogo) {
    case 1:
    spiralInRainbow();
    break;
    case 2:
    spiralOutRainbow();
    break;
    case 3:
    inverseTracer();
    break;
    case 4:
    for(int i = 0; i < random(1, 10); i++) {
      spiralInRainbow();
    }
    for(int i = 0; i < random(1, 10); i++) {
      spiralOutRainbow();
    }
    for(int i = 0; i < random(1, 10); i++) {
      inverseTracer();
    }
    break;
    default:
    spiralInRainbow();
    break;
  }
}

void colorWordsRGB(CRGB color) {
  for(int i = 0; i < MOONBASEWORDS_SIZE; i++) {
    leds[MOONBASEWORDS[i]] = color;
  }
  LEDS.show();
}

void colorWordsHSV(CHSV color) {
  for(int i = 0; i < MOONBASEWORDS_SIZE; i++) {
    leds[MOONBASEWORDS[i]] = color;
  }
  LEDS.show();
}

void clearRGB(CRGB color) {
  for(int i = 0; i < NUM_STRIPS * NUM_LEDS_PER_STRIP; i++) {
    leds[i] = color;
  }
}

void clearHSV(CHSV color) {
  for(int i = 0; i < NUM_STRIPS * NUM_LEDS_PER_STRIP; i++) {
    leds[i] = color;
  }
}

void spiralTracerIn(CRGB color, int spiralSpeed){
  for(int i = 5; i > 0; i--) {
    switch (i) {
      case 5:
      for(int j = 7; j > -1; j--) {
        leds[WING5_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 4:
      for(int j = 7; j > -1; j--) {
        leds[WING4_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 3:
      for(int j = 7; j > -1; j--) {
        leds[WING3_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 2:
      for(int j = 7; j > -1; j--) {
        leds[WING2_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 1:
      for(int j = 7; j > -1; j--) {
        leds[WING1_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
    }
  }

  for(int i = 5; i > 0; i--) {
    switch (i) {
      case 5:
      for(int j = 7; j > -1; j--) {
        leds[WING5_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 4:
      for(int j = 7; j > -1; j--) {
        leds[WING4_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 3:
      for(int j = 7; j > -1; j--) {
        leds[WING3_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 2:
      for(int j = 7; j > -1; j--) {
        leds[WING2_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 1:
      for(int j = 7; j > -1; j--) {
        leds[WING1_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
    }
  }

  for (int i = 5; i > -1; i--) {
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
  }
}

void spiralTracerOut(CRGB color, int spiralSpeed){
  for (int i = 0; i < 6; i++) {
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(spiralSpeed);
  }

  for(int i = 1; i < 6; i++) {
    switch (i) {
      case 5:
      for(int j = 0; j < 8; j++) {
        leds[WING5_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 4:
      for(int j = 0; j < 8; j++) {
        leds[WING4_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 3:
      for(int j = 0; j < 8; j++) {
        leds[WING3_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 2:
      for(int j = 0; j < 8; j++) {
        leds[WING2_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
      case 1:
      for(int j = 0; j < 8; j++) {
        leds[WING1_INNER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 3);
      }
      break;
    }
  }

  for(int i = 1; i < 6; i++) {
    switch (i) {
      case 5:
      for(int j = 0; j < 8; j++) {
        leds[WING5_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 4:
      for(int j = 0; j < 8; j++) {
        leds[WING4_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 3:
      for(int j = 0; j < 8; j++) {
        leds[WING3_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 2:
      for(int j = 0; j < 8; j++) {
        leds[WING2_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
      case 1:
      for(int j = 0; j < 8; j++) {
        leds[WING1_OUTER[j]] = color;
        LEDS.show();
        delayMicroseconds(spiralSpeed * 6);
      }
      break;
    }
  }
}

void rainbowTracer() {
  clearRGB(CRGB::Black);
  for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
    CHSV hsvColor = CHSV(h, serialInputSaturation, serialInputBrightness);
    CRGB rgbColor;
    hsv2rgb_rainbow(hsvColor, rgbColor);
    spiralTracerIn(rgbColor, serialInputSpiralSpeed);
    pinwheelOffset =  h + serialInputColorJump;
  }
  pinwheelOffset = pinwheelOffset - 255;
}

void inverseTracer() {
  for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
    clearHSV(CHSV(h, serialInputSaturation, serialInputBrightness));
    CRGB inverseColor =  -leds[0];
    spiralTracerIn(inverseColor, serialInputSpiralSpeed);
    inverseColor =  -leds[0];
    spiralTracerOut(inverseColor, serialInputSpiralSpeed);
    pinwheelOffset =  h + serialInputColorJump;
  }
  pinwheelOffset = pinwheelOffset - 255;
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
    if (inChar == '^') {
      serialFlag = '^';
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
  Serial1.println(inputString);
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
      serialInputPatternModeLogo =  number;
    }
    if (serialFlag == '^') {
      serialInputPatternModeWords =  number;
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
    LEDS.show();
    delayMicroseconds(spinSpeed);
  }
}

void spiralInRainbow() {
  CHSV color;
  for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
    color = CHSV(h, serialInputSaturation, serialInputBrightness);
    outInWords(color, serialInputSpiralSpeed);
    spiralMoonbaseIn(color, serialInputSpiralSpeed);
    pinwheelOffset =  h + serialInputColorJump;
  }
  pinwheelOffset = pinwheelOffset - 255;
}

void spiralOutRainbow() {
  CHSV color;
  for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
    color = CHSV(h, serialInputSaturation, serialInputBrightness);
    spiralMoonbaseOut(color, serialInputSpiralSpeed);
    inOutWords(color, serialInputSpiralSpeed);
    pinwheelOffset =  h + serialInputColorJump;
  }
  pinwheelOffset = pinwheelOffset - 255;
}

void inOutWords(CHSV color, int delayTime) {
  for(int i = 0; i < N_SIZE; i++) {
    leds[N[i]] = color;
  }
  for(int i = 0; i < B_SIZE; i++) {
    leds[B[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 150);

  for(int i = 0; i < O2_SIZE; i++) {
    leds[O2[i]] = color;
  }
  for(int i = 0; i < A_SIZE; i++) {
    leds[A[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 150);

  for(int i = 0; i < O1_SIZE; i++) {
    leds[O1[i]] = color;
  }
  for(int i = 0; i < S_SIZE; i++) {
    leds[S[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 150);

  for(int i = 0; i < M_SIZE; i++) {
    leds[M[i]] = color;
  }
  for(int i = 0; i < E_SIZE; i++) {
    leds[E[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 100);
}

void outInWords(CHSV color, int delayTime) {

  for(int i = 0; i < M_SIZE; i++) {
    leds[M[i]] = color;
  }
  for(int i = 0; i < E_SIZE; i++) {
    leds[E[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 100);

  for(int i = 0; i < O1_SIZE; i++) {
    leds[O1[i]] = color;
  }
  for(int i = 0; i < S_SIZE; i++) {
    leds[S[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 150);

  for(int i = 0; i < O2_SIZE; i++) {
    leds[O2[i]] = color;
  }
  for(int i = 0; i < A_SIZE; i++) {
    leds[A[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 150);

  for(int i = 0; i < N_SIZE; i++) {
    leds[N[i]] = color;
  }
  for(int i = 0; i < B_SIZE; i++) {
    leds[B[i]] = color;
  }
  LEDS.show();
  delayMicroseconds(delayTime * 150);
}

void spiralMoonbaseIn(CHSV color, int delayTime) {
  // Spiral in
  for (int i = 7; i > -1; i--) {
    leds[WING5_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[WING4_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[WING3_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[WING2_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[WING1_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
  }
  for (int i = 7; i > -1; i--) {
    leds[WING5_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING4_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING3_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING2_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING1_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
  }
  for (int i = 5; i > -1; i--) {
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
  }
}

void spiralMoonbaseOut(CHSV color, int delayTime) {
  // Spiral in
  for (int i = 0; i < 5; i++) {
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
    leds[CENTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime);
  }
  for (int i = 0; i < 8; i++) {
    leds[WING5_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING4_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING3_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING2_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
    leds[WING1_INNER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 3);
  }
  for (int i = 0; i < 8; i++) {
    leds[WING5_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[WING4_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[WING3_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[WING2_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
    leds[WING1_OUTER[i]] = color;
    LEDS.show();
    delayMicroseconds(delayTime * 6);
  }
}
