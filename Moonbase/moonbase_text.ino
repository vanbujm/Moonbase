// // MultipleStripsInOneArray - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// // using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on three
// // different pins, each strip will be referring to a different part of the single led array
//
// #include "FastLED.h"
//
// #define NUM_STRIPS 2
// #define NUM_LEDS_PER_STRIP 126
// #define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
//
// CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
//
// #define BRIGHTNESS          255
//
// String inputString = "";         // a string to hold incoming data
// boolean stringComplete = false;  // whether the string is complete
//
//
// void setup() {
//     // reserve 200 bytes for the inputString:
//   inputString.reserve(200);
//   delay(1000); // 3 second delay for recovery
//   Serial.begin(9600);
//   Serial.println("Serial connected!");
//
//   // tell FastLED there's n NEOPIXEL leds on pin 10, starting at index 0 in the led array
//   FastLED.addLeds<NEOPIXEL, 6>(leds, 0, NUM_LEDS_PER_STRIP);
//
//   // tell FastLED there's n NEOPIXEL leds on pin 11, starting at index n in the led array
//   FastLED.addLeds<NEOPIXEL, 7>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
//
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
// int serialInputSpiralSpeed = 2;
// int serialInputColorJump = 1;
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
// void spiralOutRainbow() {
//   static uint8_t hue = 0;
//
//   for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//     leds[j] = CHSV((32*0) + hue+j*2,serialInputSaturation,serialInputBrightness);
//   }
//
//   for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//     leds[251 - j] = CHSV((32*1) + hue+j*2,serialInputSaturation,serialInputBrightness);
//   }
//
//
//   hue = hue + serialInputColorJump;
//
//   LEDS.show();
//   LEDS.delay(serialInputSpiralSpeed);
// }
//
//
// void spiralInRainbow() {
//   static uint8_t hue = 0;
//
//   for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//     leds[126 - j] = CHSV((32*0) + hue+j*2,serialInputSaturation,serialInputBrightness);
//   }
//
//   for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
//     leds[126 + j] = CHSV((32*1) + hue+j*2,serialInputSaturation,serialInputBrightness);
//   }
//
//
//   hue = hue + serialInputColorJump;
//
//   LEDS.show();
//   LEDS.delay(serialInputSpiralSpeed);
// }
//
//
