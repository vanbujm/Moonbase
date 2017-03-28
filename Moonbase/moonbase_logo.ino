// #define USE_OCTOWS2811
// #include<OctoWS2811.h>
// #include "FastLED.h"
//
// #define NUM_LEDS_PER_STRIP 17
// #define NUM_STRIPS 5
//
// CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
//
// #define BRIGHTNESS          255
//
//
// // MOONBASE PARTS
// int CENTER[5] = {0, 17, 34, 51, 68};
//
// int WING1_INNER[8] = {1, 2, 3, 4, 5, 6, 7, 8};
// int WING1_OUTER[8] = {9, 10, 11, 12, 13, 14, 15, 16};
//
// int WING2_INNER[8] = {18, 19, 20, 21, 22, 23, 24, 25};
// int WING2_OUTER[8] = {26, 27, 28, 29, 30, 31, 32, 33};
//
// int WING3_INNER[8] = {35, 36, 37, 38, 39, 40, 41, 42};
// int WING3_OUTER[8] = {43, 44, 45, 46, 47, 48, 49, 50};
//
// int WING4_INNER[8] = {52, 53, 54, 55, 56, 57, 58, 59};
// int WING4_OUTER[8] = {60, 61, 62, 63, 64, 65, 66, 67};
//
// int WING5_INNER[8] = {69, 70, 71, 72, 73, 74, 75, 76};
// int WING5_OUTER[8] = {77, 78, 79, 80, 81, 82, 83, 84};
//
//
// String inputString = "";         // a string to hold incoming data
// boolean stringComplete = false;  // whether the string is complete
//
// void setup() {
//   // reserve 200 bytes for the inputString:
//   inputString.reserve(200);
//   delay(1000); // 3 second delay for recovery
//   Serial.begin(9600);
//   Serial.println("Serial connected!");
//
//   // tell LEDS about the LED strip configuration
//   LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
//   // set master brightness control
//   LEDS.setBrightness(BRIGHTNESS);
//
//   for (int i = 0; i < NUM_STRIPS * NUM_LEDS_PER_STRIP; i++) {
//     leds[i] =  CRGB::Black;
//     LEDS.show();
//   }
// }
//
// String inString = "";
// boolean flipFlop = true;
// int pinwheelOffset = 0;
//
// int serialInputSpiralSpeed = 15;
// int serialInputColorJump = 17;
// int serialInputSaturation = 255;
// int serialInputBrightness = 64;
//
// int serialInputPatternMode = 1;
//
// char serialFlag = '!';
//
// void loop() {
//   // print the string when a newline arrives:
//   //  int blendFactor = 51;
//   switch (serialInputPatternMode) {
//     case 1:
//       spiralInRainbow();
//       break;
//     case 2:
//       spiralOutRainbow();
//       break;
//     default:
//       spiralInRainbow();
//     break;
//   }
// }
// /*
//   SerialEvent occurs whenever a new data comes in the
//   hardware serial RX.  This routine is run between each
//   time loop() runs, so using delay inside loop can delay
//   response.  Multiple bytes of data may be available.
// */
// void serialEvent() {
//   while (Serial.available()) {
//     boolean shouldClear = false;
//     // get the new byte:
//     char inChar = (char)Serial.read();
//     // add it to the inputString:
//     inputString += inChar;
//     // if the incoming character is a newline, set a flag
//     // so the main loop can do something about it:
//     if (inChar == '!') {
//       serialFlag = '!';
//       assignSerial();
//       shouldClear = true;
//     }
//     if (inChar == '@') {
//       serialFlag = '@';
//       assignSerial();
//       shouldClear = true;
//     }
//     if (inChar == '#') {
//       serialFlag = '#';
//       assignSerial();
//       shouldClear = true;
//     }
//     if (inChar == '$') {
//       serialFlag = '$';
//       assignSerial();
//       shouldClear = true;
//     }
//     if (inChar == '%') {
//       serialFlag = '%';
//       assignSerial();
//       shouldClear = true;
//     }
//     if (shouldClear) {
//       inputString = "";
//     }
//   }
// }
//
// void assignSerial() {
//   Serial.println(inputString);
//   if (isValidNumber(inputString)) {
//     int number = inputString.toInt();
//     if (serialFlag == '!') {
//       serialInputColorJump =  number;
//     }
//     if (serialFlag == '@') {
//       serialInputSpiralSpeed =  number;
//     }
//     if (serialFlag == '#') {
//       serialInputSaturation =  number;
//     }
//     if (serialFlag == '$') {
//       serialInputBrightness =  number;
//     }
//     if (serialFlag == '%') {
//       serialInputPatternMode =  number;
//     }
//   }
// }
//
// boolean isValidNumber(String str) {
//   for (byte i = 0; i < str.length(); i++)
//   {
//     if (isDigit(str.charAt(i))) return true;
//   }
//   return false;
// }
//
// void pinwheelMoonbase(int s, int v, int blendFactor, int spinSpeed) {
//   for (int h = pinwheelOffset; h < 255; h += blendFactor) {
//     for (int i = 0; i < 8; i++) {
//       leds[WING5_OUTER[i]] = CHSV(h, s, v);
//
//       leds[WING4_OUTER[i]] = CHSV(h + blendFactor, s, v);
//
//       leds[WING3_OUTER[i]] = CHSV(h + blendFactor * 2, s, v);
//
//       leds[WING2_OUTER[i]] = CHSV(h + blendFactor * 3, s, v);
//
//       leds[WING1_OUTER[i]] = CHSV(h + blendFactor * 4, s, v);
//
//       leds[WING5_INNER[i]] = CHSV(h, s, v);
//
//       leds[WING4_INNER[i]] = CHSV(h + blendFactor, s, v);
//
//       leds[WING3_INNER[i]] = CHSV(h + blendFactor * 2, s, v);
//
//       leds[WING2_INNER[i]] = CHSV(h + blendFactor * 3, s, v);
//
//       leds[WING1_INNER[i]] = CHSV(h + blendFactor * 4, s, v);
//     }
//     leds[CENTER[4]] = CHSV(h, s, v);
//     leds[CENTER[3]] = CHSV(h + blendFactor, s, v);
//     leds[CENTER[2]] = CHSV(h + blendFactor * 2, s, v);
//     leds[CENTER[1]] = CHSV(h + blendFactor * 3, s, v);
//     leds[CENTER[0]] = CHSV(h + blendFactor * 4, s, v);
//     LEDS.show();
//     delay(spinSpeed);
//   }
// }
//
// void spiralInRainbow() {
//   for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
//     spiralMoonbaseIn(h, serialInputSaturation, serialInputBrightness, serialInputSpiralSpeed);
//     pinwheelOffset =  h + serialInputColorJump;
//   }
//   pinwheelOffset = pinwheelOffset - 255;
// }
//
// void spiralOutRainbow() {
//   for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
//     spiralMoonbaseOut(h, serialInputSaturation, serialInputBrightness, serialInputSpiralSpeed);
//     pinwheelOffset =  h + serialInputColorJump;
//   }
//   pinwheelOffset = pinwheelOffset - 255;
// }
//
// void spiralMoonbaseIn(int h, int s, int v, int delayTime) {
//   CHSV color( h, s, v);
//   // Spiral in
//   for (int i = 7; i > -1; i--) {
//     leds[WING5_OUTER[i]] = color;
//     leds[WING4_OUTER[i]] = color;
//     leds[WING3_OUTER[i]] = color;
//     leds[WING2_OUTER[i]] = color;
//     leds[WING1_OUTER[i]] = color;
//     LEDS.show();
//     delay(delayTime);
//   }
//   for (int i = 7; i > -1; i--) {
//     leds[WING5_INNER[i]] = color;
//     leds[WING4_INNER[i]] = color;
//     leds[WING3_INNER[i]] = color;
//     leds[WING2_INNER[i]] = color;
//     leds[WING1_INNER[i]] = color;
//     LEDS.show();
//     delay(delayTime);
//   }
//
//   for (int i = 5; i > -1; i--) {
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//   }
//   LEDS.show();
// }
//
// void spiralMoonbaseOut(int h, int s, int v, int delayTime) {
//   CHSV color( h, s, v);
//   // Spiral in
//   for (int i = 0; i < 5; i++) {
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//     leds[CENTER[i]] = color;
//   }
//   LEDS.show();
//
//   for (int i = 0; i < 8; i++) {
//     leds[WING5_INNER[i]] = color;
//     leds[WING4_INNER[i]] = color;
//     leds[WING3_INNER[i]] = color;
//     leds[WING2_INNER[i]] = color;
//     leds[WING1_INNER[i]] = color;
//     LEDS.show();
//     delay(delayTime);
//   }
//
//   for (int i = 0; i < 8; i++) {
//     leds[WING5_OUTER[i]] = color;
//     leds[WING4_OUTER[i]] = color;
//     leds[WING3_OUTER[i]] = color;
//     leds[WING2_OUTER[i]] = color;
//     leds[WING1_OUTER[i]] = color;
//     LEDS.show();
//     delay(delayTime);
//   }
//
// }
//
//
