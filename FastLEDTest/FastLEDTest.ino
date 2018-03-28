#include "FastLED.h"

#define NUM_LEDS 9
CRGB leds[NUM_LEDS];

int inPins[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int ledStates[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int previousSwitchStates[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  for( int i = 0; i < 9; i = i + 1 ) {
    pinMode(inPins[i], INPUT);
  }
}

void loop() {

  for( int i = 0; i < 9; i = i + 1 ) {    
    int switchState = digitalRead(inPins[i]);
    if (switchState != previousSwitchState[i] && switchState == 1) {
      toggleLED(i);
      updateLED(i);
    }
    previousSwitchState[i] = switchState;       
  }
  
}

void toggleLED(int i) {
  ledStates[i] = (ledStates[i] == 1) ? 0 : 1;
}

void updateLED(int i) {
  leds[i] = (ledStates[i] == 1) ? CRGB::White : CRGB::Black;
  FastLED.show();  
}
