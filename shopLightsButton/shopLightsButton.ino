#include <FastLED.h>

// NEOPIXEL DEFINITIONS -----------------------------------------------------------------------------
#define NUM_LEDS 135
#define DATA_PIN 5      // Green
#define CLOCK_PIN 6     // Blue
CRGB leds[NUM_LEDS];

// BUTTON DEFINITIONS -----------------------------------------------------------------------------
const int buttonPin = 2;
long debounceDelay = 98;
long lastDebounceTime = 0;        // the last time the output pin was toggled
boolean currentState = LOW;       //stroage for current button state
boolean lastState = LOW;          //storage for last button state
boolean neopixelState = LOW;      //storage for the current state of the LED (off/on)


void setup() {
  Serial.begin(9600);             //initialize Serial connection

  // BUTTON SETUP --------------
  pinMode(buttonPin, INPUT);      //this time we will set the pin as INPUT

  // LEDS SETUP --------------
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
  lightsOff();
  FastLED.show();
}

void loop() {

  currentState = digitalRead(buttonPin);

  if ( (millis() - lastDebounceTime) > debounceDelay) {

    if (currentState == HIGH && lastState == LOW) {         //if button has just been pressed
      Serial.println("pressed");
      delay(1);                                 //crude form of button debouncing

      //toggle the state of the Neopixels
      if (neopixelState == HIGH && currentState == HIGH ) {
        neopixelState = LOW;
        Serial.println("Off");
        lightsOff();
        lastDebounceTime = millis();          //set the current time
      } else {
        neopixelState = HIGH;
        Serial.println("On");
        lightsOn();
        lastDebounceTime = millis();          //set the current time
      }
    }
    lastState = currentState;
  }
}







// FUNCTION FADING LIGHTS ON  -----------------------------------------------------------------------------

void lightsOn() {
  int lightsOnMaxBrightness = 64;
  int lightsOnMinBrightness = 0;

  for (int i = lightsOnMinBrightness; i < lightsOnMaxBrightness; i++) {
    lightsOnMinBrightness = i;
    FastLED.show();
    delay(25);
    for ( int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CRGB(lightsOnMinBrightness);
    }
  }
}


// FUNCTION FADING LIGHTS OFF  -----------------------------------------------------------------------------

void lightsOff() {
  int lightsOffMaxBrightness = 64;
  int lightsOffMinBrightness = -1;

  for (int i = lightsOffMaxBrightness; i > lightsOffMinBrightness; i--) {
    lightsOffMaxBrightness = i;
    FastLED.show();
    delay(25);
    for ( int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CRGB(lightsOffMaxBrightness);
    }
  }
}



