//
//
// #include <Arduino.h>
// #define USE_OCTOWS2811
// #include<OctoWS2811.h>
// #include "FastLED.h"
//
// #define NUM_LEDS_PER_STRIP 17
// // #define NUM_STRIPS 5
// // CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
//
// CRGB wing1[NUM_LEDS_PER_STRIP];
// CRGB wing2[NUM_LEDS_PER_STRIP];
// CRGB wing3[NUM_LEDS_PER_STRIP];
// CRGB wing4[NUM_LEDS_PER_STRIP];
// CRGB wing5[NUM_LEDS_PER_STRIP];
//
// #define BRIGHTNESS          255
//
// void spiralTracerIn(int h, int s, int v, int spiralSpeed);
// void rainbowTracer();
// void serialEvent();
// void assignSerial();
// boolean isValidNumber(String str);
// void pinwheelMoonbase(int s, int v, int blendFactor, int spinSpeed);
// void spiralInRainbow();
// void spiralOutRainbow();
// void spiralMoonbaseIn(int h, int s, int v, int spiralSpeed);
// void spiralMoonbaseOut(int h, int s, int v, int spiralSpeed);
//
// String inputString = "";         // a string to hold incoming data
// boolean stringComplete = false;  // whether the string is complete
//
// void setup() {
//   // reserve 200 bytes for the inputString:
//   inputString.reserve(200);
//   delayMicroseconds(1000); // 3 second delayMicroseconds for recovery
//   Serial.begin(9600);
//   Serial.println("Serial connected!");
//
//   // tell LEDS about the LED strip configuration
//   LEDS.addLeds<OCTOWS2811>(wing1, NUM_LEDS_PER_STRIP);
//   LEDS.addLeds<OCTOWS2811>(wing2, NUM_LEDS_PER_STRIP);
//   LEDS.addLeds<OCTOWS2811>(wing3, NUM_LEDS_PER_STRIP);
//   LEDS.addLeds<OCTOWS2811>(wing5, NUM_LEDS_PER_STRIP);
//   LEDS.addLeds<OCTOWS2811>(wing6, NUM_LEDS_PER_STRIP);
//
//   // set master brightness control
//   LEDS.setBrightness(BRIGHTNESS);
//
//   for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//     // leds[i] =  CRGB::Black;
//     wing1[i] = CRGB::Black;
//     wing2[i] = CRGB::Black;
//     wing3[i] = CRGB::Black;
//     wing4[i] = CRGB::Black;
//     wing5[i] = CRGB::Black;
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
// int serialInputBrightness = 255;
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
//     spiralInRainbow();
//     break;
//     case 2:
//     spiralOutRainbow();
//     break;
//     case 3:
//     rainbowTracer();
//     break;
//     default:
//     spiralInRainbow();
//     break;
//   }
// }
//
// void spiralTracerIn(int h, int s, int v, int spiralSpeed){
//   for(int i = NUM_LEDS_PER_STRIP -1; i > -1; i++) {
//     for(int j = 1; j < 6; j++) {
//       switch(j) {
//         case 1:
//         wing1[i] = CHSV(h,s,v);
//         delayMicroseconds(spiralSpeed);
//         break;
//         case 2:
//         wing2[i] = CHSV(h,s,v);
//         delayMicroseconds(spiralSpeed);
//         break;
//         case 3:
//         wing3[i] = CHSV(h,s,v);
//         delayMicroseconds(spiralSpeed);
//         break;
//         case 4:
//         wing4[i] = CHSV(h,s,v);
//         delayMicroseconds(spiralSpeed);
//         break;
//         case 5:
//         wing5[i] = CHSV(h,s,v);
//         delayMicroseconds(spiralSpeed);
//         break;
//       }
//     }
//   }
// }
//
// void rainbowTracer() {
//   for (int h = pinwheelOffset; h < 255; h += serialInputColorJump) {
//     spiralTracerIn(h, serialInputSaturation, serialInputBrightness, serialInputSpiralSpeed);
//     pinwheelOffset =  h + serialInputColorJump;
//   }
//   pinwheelOffset = pinwheelOffset - 255;
// }
//
// /*
// SerialEvent occurs whenever a new data comes in the
// hardware serial RX.  This routine is run between each
// time loop() runs, so using delayMicroseconds inside loop can delayMicroseconds
// response.  Multiple bytes of data may be available.
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
//     for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//       wing1[i] = CHSV(h, s, v);
//       LEDS.show();
//       delayMicroseconds(spinSpeed);
//       wing2[i] = CHSV(h + blendFactor, s, v);
//       LEDS.show();
//       delayMicroseconds(spinSpeed);
//       wing3[i] = CHSV(h + blendFactor * 2, s, v);
//       LEDS.show();
//       delayMicroseconds(spinSpeed);
//       wing4[i] = CHSV(h + blendFactor * 3, s, v);
//       LEDS.show();
//       delayMicroseconds(spinSpeed);
//       wing5[i] = CHSV(h + blendFactor * 4, s, v);
//       LEDS.show();
//       delayMicroseconds(spinSpeed);
//     }
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
// void spiralMoonbaseIn(int h, int s, int v, int spiralSpeed) {
//   CHSV color( h, s, v);
//   // Spiral in
//   for(int i = NUM_LEDS_PER_STRIP - 1; i > -1; i--) {
//     wing1[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing2[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing3[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing4[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing5[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//   }
// }
//
// void spiralMoonbaseOut(int h, int s, int v, int spiralSpeed) {
//   CHSV color( h, s, v);
//   for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//     wing1[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing2[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing3[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing4[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//     wing5[i] = color;
//     LEDS.show();
//     delayMicroseconds(spiralSpeed);
//   }
// }
