#include <Arduino.h>

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

void serialEvent();
void assignSerial();
boolean isValidNumber(String str);


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN 7
//#define CLK_PIN   4
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 89
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND 120
#define tenDegrees 0.17
#define PI 3.1415926535897932384626433832795

// H20 PARTS HeightMap
int H20_GRID[28][18] = {
  {-1, -1, -1, -1, -1, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20},
  {48, 47, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {49, -1, 46, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1},
  {50, -1, -1, 45, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, -1},
  {51, -1, -1, -1, 44, -1, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1},
  {52, -1, -1, -1, -1, 43, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1},
  {53, -1, -1, -1, -1, -1, 42, -1, -1, -1, 37, -1, -1, -1, -1, -1, -1, -1},
  {54, -1, -1, -1, -1, -1, -1, 41, 40, 39, 38, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, 79, 80, 81, 82, 83, 84, 85, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, 78, -1, -1, -1, -1, -1, -1, -1, 86, -1, -1, -1},
  {-1, -1, -1, -1, -1, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1, 87, -1, -1},
  {-1, -1, -1, -1, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 88, -1},
  {-1, -1, -1, 75, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 55},
  {-1, -1, -1, 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56},
  {-1, -1, -1, 73, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 57},
  {-1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 58},
  {-1, -1, -1, -1, 71, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 59, -1},
  {-1, -1, -1, -1, -1, 70, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60, -1, -1},
  {-1, -1, -1, -1, -1, -1, 69, -1, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, 68, 67, 66, 65, 64, 63, 62, -1, -1, -1, -1}};

  String inputString = "";        // a string to hold incoming data
  boolean stringComplete = false; // whether the string is complete

  void setup()
  {
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

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
  }

  String inString = "";
  boolean flipFlop = true;
  int pinwheelOffset = 0;

  int serialInputSpiralSpeed = 120;
  int serialInputColorJump = 17;
  int serialInputSaturation = 255;
  int serialInputBrightness = 255;

  int serialInputPatternMode = 1;

  char serialFlag = '!';

  void loop()
  {
    for(int h = 165; h > 130; h--){
      int bubble = (int)random(100);
      for(int i=0; i < 28; i++) {
        for(int j=0; j < 18; j++) {
          int ledNum = H20_GRID[i][j];
          if((i+2)%bubble == 0 && (i == 0 || i == 8 || i == 16 || i == 27) ) {
            if(ledNum != -1) {
              leds[H20_GRID[i][j]] = CRGB::White;
              FastLED.show();
              leds[H20_GRID[i][j]] = CHSV(h, serialInputSaturation, serialInputBrightness);
              delay(100);
            }
          }
          else {
            if(ledNum != -1) {
              leds[H20_GRID[i][j]] = CHSV(h, serialInputSaturation, serialInputBrightness);
            }
          }
        }
      }
      FastLED.show();
      delay(serialInputSpiralSpeed);
    }
    for(int h = 130; h < 165; h++){
      for(int i=0; i < 28; i++) {
        for(int j=0; j < 18; j++) {
          leds[H20_GRID[i][j]] = CHSV(h, serialInputSaturation, serialInputBrightness);
        }
      }
      FastLED.show();
      delay(serialInputSpiralSpeed);
    }
  }
  //
  // int maxDark = 255;
  // int lightColor = 0;
  // int toIncrement = 0;
  // for(int c = 165; c > 130; c-=3 ) {
  //   for(int t=0; t< 28; t+=2) {
  //     for(int x=0; x < 28; x++) {
  //       lightColor = 10*(sin((x*PI)/28 - t) + 1);
  //       toIncrement = (maxDark - lightColor)/3;
  //       for(int i = 0; i < 18; i++) {
  //         int ledNum = H20_GRID[x][i];
  //         if(ledNum != -1) {
  //           leds[ledNum] = CHSV(c, 255 - (toIncrement * (i/6)) , 255);
  //         }
  //       }
  //     }
  //   FastLED.show();
  //   delay(150);
  //   }
  // }
  // for(int c = 130; c < 165; c+=3 ) {
  //   for(int t=0; t< 28; t+=2) {
  //     for(int x=0; x < 28; x++) {
  //       lightColor = 10*(sin((x*PI)/28 - t) + 1);
  //       toIncrement = (maxDark - lightColor)/3;
  //       for(int i = 0; i < 18; i++) {
  //         int ledNum = H20_GRID[x][i];
  //         if(ledNum != -1) {
  //           leds[ledNum] = CHSV(c, 255 - (toIncrement * (i/6)) , 255);
  //         }
  //       }
  //     }
  //   FastLED.show();
  //   delay(150);
  //   }
  // }

  /*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
  */
  void serialEvent()
  {
    while (Serial.available())
    {
      boolean shouldClear = false;
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '!')
      {
        serialFlag = '!';
        assignSerial();
        shouldClear = true;
      }
      if (inChar == '@')
      {
        serialFlag = '@';
        assignSerial();
        shouldClear = true;
      }
      if (inChar == '#')
      {
        serialFlag = '#';
        assignSerial();
        shouldClear = true;
      }
      if (inChar == '$')
      {
        serialFlag = '$';
        assignSerial();
        shouldClear = true;
      }
      if (inChar == '%')
      {
        serialFlag = '%';
        assignSerial();
        shouldClear = true;
      }
      if (shouldClear)
      {
        inputString = "";
      }
    }
  }

  void assignSerial()
  {
    Serial.println(inputString);
    if (isValidNumber(inputString))
    {
      int number = inputString.toInt();
      if (serialFlag == '!')
      {
        serialInputColorJump = number;
      }
      if (serialFlag == '@')
      {
        serialInputSpiralSpeed = number;
      }
      if (serialFlag == '#')
      {
        serialInputSaturation = number;
      }
      if (serialFlag == '$')
      {
        serialInputBrightness = number;
      }
      if (serialFlag == '%')
      {
        serialInputPatternMode = number;
      }
    }
  }

  boolean isValidNumber(String str)
  {
    for (byte i = 0; i < str.length(); i++)
    {
      if (isDigit(str.charAt(i)))
      return true;
    }
    return false;
  }
