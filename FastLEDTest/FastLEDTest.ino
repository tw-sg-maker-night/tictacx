#include "FastLED.h"

#define NUM_LEDS 9
#define BRIGHTNESS  16
CRGB leds[NUM_LEDS];

int inPins[9] = { 1, 1, 1, 1, 7, 8, 1, 1, 1 };
int ledStates[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int previousSwitchStates[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  for( int i = 0; i < 9; i = i + 1 ) {
    pinMode(inPins[i], INPUT);
  }
}

void loop() {

  for( int i = 0; i < 9; i = i + 1 ) {    
    int switchState = digitalRead(inPins[i]);
    if (switchState != previousSwitchStates[i] && switchState == 1) {
      toggleLED(i);
    }
    previousSwitchStates[i] = switchState;       
  }

  for( int i = 0; i < 9; i = i + 1 ) {        
    leds[i] = (ledStates[i] == 1) ? CRGB::White : CRGB::Black;  
    FastLED.show();
  }  
  
}

void toggleLED(int i) {
  ledStates[i] = (ledStates[i] == 1) ? 0 : 1;
}
