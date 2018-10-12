#include <FastLED.h>
#include <CapacitiveSensor.h>

// NEOPIXEL DEFINITIONS -----------------------------------------------------------------------------
#define NUM_LEDS 135
#define DATA_PIN 5      // Green
#define CLOCK_PIN 6     // Blue    Comment out for Neopixels
CRGB leds[NUM_LEDS];


// BUTTON DEFINITIONS -----------------------------------------------------------------------------
CapacitiveSensor capSensor = CapacitiveSensor(4, 2);
int threshold = 1000;
boolean currentState = LOW;       // stroage for current button state
boolean lastState = LOW;          // storage for last button state
boolean neopixelState = LOW;      // storage for the current state of the LED (off/on)


void setup() {
  Serial.begin(9600);                               // initialize Serial connection
  capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

  // LEDS SETUP --------------
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);      // Comment out for Neopixels
  // FastLED.addLeds<WS2811, DATA_PIN,RGB>(leds, NUM_LEDS);         // Uncomment for Neopixels
  lightsOff();
  FastLED.show();
}

void loop() {

  long capValue = capSensor.capacitiveSensor(30);
  currentState = digitalRead(capValue);

  if (capValue > threshold) {
    if (currentState == HIGH && lastState == LOW) {         // if button has just been pressed
      Serial.println("pressed");
      delay(1);                                             // crude form of button debouncing

      //toggle the state of the Neopixels

      if (neopixelState == HIGH) {
        neopixelState = LOW;
        Serial.println("Off");
        lightsOff();

      } else {
        neopixelState = HIGH;
        Serial.println("On");
        lightsOn();
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



