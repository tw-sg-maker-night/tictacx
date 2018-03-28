#include "FastLED.h"

#define NUM_LEDS 9

int inPin = 7;
int inPin6 = 8;
int ledState = 0;
int ledState6 = 0;
int previousSwitchState = 0;
int previousSwitchState6 = 0;
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  pinMode(inPin, INPUT);    // declare pushbutton as input
}

void loop() {

  int switchState = digitalRead(inPin);
  if (switchState != previousSwitchState && switchState == 1) {
    toggleLED();
  }
  previousSwitchState = switchState;


  switchState = digitalRead(inPin6);
  if (switchState != previousSwitchState6 && switchState == 1) {
    toggleLED6();
  }
  previousSwitchState6 = switchState;


  updateLED();
}

void toggleLED() {
  if (ledState == 1) {
    ledState = 0;
  } else {
    ledState = 1;
  }
}

void toggleLED6() {
  if (ledState6 == 1) {
    ledState6 = 0;
  } else {
    ledState6 = 1;
  }
}

void updateLED() {
  if (ledState) {
    leds[4] = CRGB::White;
    FastLED.show();
  } else {
    leds[4] = CRGB::Black;
    FastLED.show();
  }

  if (ledState6) {
    leds[5] = CRGB::White;
    FastLED.show();
  } else {
    leds[5] = CRGB::Black;
    FastLED.show();
  }

}
