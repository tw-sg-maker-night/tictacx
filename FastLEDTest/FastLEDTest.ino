#include <StackArray.h>
#include "FastLED.h"

#define NUM_LEDS 9
#define BRIGHTNESS  16
CRGB leds[NUM_LEDS];

int inPins[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10 };
int ledStates[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int previousSwitchStates[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int currentPlayer = 1;
StackArray <int> history;

void setup() {
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  Serial.begin(9600);
  for ( int i = 0; i < 9; i = i + 1 ) {
    pinMode(inPins[i], INPUT);
  }
}

void loop() {
  for ( int i = 0; i < 9; i = i + 1 ) {
    int switchState = digitalRead(inPins[i]);
    if (switchState != previousSwitchStates[i] && switchState == HIGH) {
      toggleLED(i);
      undoOrTakeTurn(i);
      nextMove();
    }
    previousSwitchStates[i] = switchState;
  }
  FastLED.show();
}

void toggleLED(int currentSwitch) {
  ledStates[currentSwitch] = (ledStates[currentSwitch] == HIGH) ? LOW : HIGH;
  Serial.println("toggle");
  Serial.println(currentPlayer);

  CRGB color = (currentPlayer == 1) ? CRGB::Blue : CRGB::Red;
  leds[currentSwitch] = (ledStates[currentSwitch] != LOW) ? color : CRGB::Black;
}

void undoOrTakeTurn(int currentSwitch) {
  if (!history.isEmpty() && history.peek() == currentSwitch) {
    Serial.println("Undo");
    history.pop();
    return;
  }
  Serial.println("Take turn");
  history.push(currentSwitch);
}

void nextMove() {
  currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

