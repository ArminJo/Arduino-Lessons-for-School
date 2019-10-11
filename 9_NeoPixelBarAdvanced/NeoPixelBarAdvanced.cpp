/*
 * Lessons with 16 LEDs NeoPixel bar
 * Create a moving pattern and a moving rainbow
 *
 * Copyright 2018 Armin Joachimsmeyer
 * This code is released under GPLv3 license.
 */

/*
 * WICHTIGE TASTENKOMBINATIONEN
 * Formatieren: "strg" + "F"
 * Definition finden: "F3"
 * Autocompletion: "strg" + Leertaste
 * Verwendung suchen: "strg" + "G"
 *
 */

#include <Arduino.h>
#include "Breadboard.h"

#include <Adafruit_NeoPixel.h>

#define VERSION "1.0"

// How many NeoPixels are mounted on the bar?
#define NUMPIXELS      16

// Forward declarations
uint32_t Wheel(uint8_t WheelPos);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel MyNeoPixelBar = Adafruit_NeoPixel(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Global variables for pattern
int Delay = 200; // delay between sub patterns

uint8_t ActivePattern;  // which pattern is running
#define PATTERN_MOVING_POINT        0
#define PATTERN_RAINBOW_CYCLE       1

uint16_t TotalSteps;  	// total number of steps in the pattern. will be compared with Index for basic patterns.
int Index; 				// Counter for basic pattern. Current step within the pattern. Counter for basic patterns. Step counter of snake.
bool DirectionIsUP;     // direction to run the pattern

void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

	MyNeoPixelBar.begin(); // This initializes the NeoPixel library.
	Index = 0;
	ActivePattern = PATTERN_MOVING_POINT;
	TotalSteps = NUMPIXELS + 3 * (NUMPIXELS - 1);
}

/*
 * Aufgaben:
 * 1. Umdrehen der Richtung am den Enden. Benutze Index und DirectionIsUP.
 * 2. Einlesen eines Wertes für Delay. Benutze analogRead(PIN_POTENTIOMETER) und map().
 * 3. Ausgeben eines sich ändernden Regenbogens. Benutze Index, TotalSteps und Wheel();
 */
void loop() {

	int tDelay;

	for (int i = 0; i < NUMPIXELS; i++) {
		if (i == Index) {
			// Color takes RGB values, from 0,0,0 up to 255,255,255
			MyNeoPixelBar.setPixelColor(i, MyNeoPixelBar.Color(0, 128, 0)); // Moderately bright green color.
		} else {
			MyNeoPixelBar.setPixelColor(i, MyNeoPixelBar.Color(0, 0, 0));
		}
	}

	MyNeoPixelBar.show(); // This sends the updated pixel color to the hardware.
	Index++; // increment index for next loop.

	delay(Delay); // Delay for a period of time (in milliseconds).

}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(uint8_t WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return Adafruit_NeoPixel::Color(255 - (WheelPos * 3), 0, WheelPos * 3);
	} else if (WheelPos < 170) {
		WheelPos -= 85;
		return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - (WheelPos * 3));
	} else {
		WheelPos -= 170;
		return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - (WheelPos * 3), 0);
	}
}
