/*
 * Lessons with 8x8 LEDs NeoPixel matrix
 */

/*
 * WICHTIGE TASTENKOMBINATIONEN
 * Formatieren: "strg" + "F"
 * Definition finden: "F3"
 * Autocompletion: "strg" + Leertaste
 * Verwendung suchen: "strg" + "G"
 *
 * Vergeichsoperatoren sind: "==", "!=", ">=", ">=".
 * Bedingungen werden verknüpft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#include <MatrixNeoPixel.h>
#include <math.h>

#define VERSION_EXAMPLE "1.0"

#define NEOPIXEL_MATRIX_NUM_ROWS   		8
#define NEOPIXEL_MATRIX_NUM_COLUMNS   	8
// How many NeoPixels are mounted on the bar?
#define NEOPIXEL_MATRIX_NUM_PIXELS   	(NEOPIXEL_MATRIX_NUM_COLUMNS * NEOPIXEL_MATRIX_NUM_ROWS)

// Forward declarations
uint32_t Wheel(uint8_t WheelPos);

/*
 * When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
 * Specify your matrix geometry as 4th parameter.
 * ....BOTTOM ....RIGHT specify the position of the zeroth pixel.
 * See MatrixNeoPatterns.h for further explanation.
 */
MatrixNeoPixel NeoPixelMatrix = MatrixNeoPixel(NEOPIXEL_MATRIX_NUM_COLUMNS, NEOPIXEL_MATRIX_NUM_ROWS, PIN_NEOPIXEL,
NEO_MATRIX_BOTTOM | NEO_MATRIX_RIGHT | NEO_MATRIX_ROWS | NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));
	initBreadboardPins();

	NeoPixelMatrix.begin(); // This initializes the MatrixNeoPixel library.

	/*
	 * Setzte die Diagonalen auf rot. Die Parameter der color Funktion bedeuten: Color(<rot>, <grün>, <blau>)
	 */
	uint8_t tValue = 255;

	for (unsigned int i = 0; i < NEOPIXEL_MATRIX_NUM_COLUMNS; i++) {
		Serial.print("Value=");
		Serial.println(tValue);
		NeoPixelMatrix.setMatrixPixelColor(i, i, NeoPixelMatrix.Color(tValue, 0, 0)); // Red
		NeoPixelMatrix.setMatrixPixelColor(NEOPIXEL_MATRIX_NUM_COLUMNS - i - 1, i, NeoPixelMatrix.Color(tValue, 0, 0)); // Red
	}
	NeoPixelMatrix.show();
	delay(4000);
	NeoPixelMatrix.clear();

}

void loop() {
	static uint8_t tWheelOffset = 0; // "static" -> keep value between loops

	if (millis() < 14000) {
		/*
		 * Aufgabe 3. Der Regenbogen, der unten ausgegeben wird, soll auf der ganzen Matrix angezeigt werden.
		 */
		for (unsigned int i = 0; i < NEOPIXEL_MATRIX_NUM_COLUMNS; i++) {
			for (unsigned int j = 0; j < NEOPIXEL_MATRIX_NUM_ROWS; j++) {
				NeoPixelMatrix.setMatrixPixelColor(i, j,
						Wheel(tWheelOffset + (tWheelOffset + (i * (256 / NEOPIXEL_MATRIX_NUM_COLUMNS)))));
			}
		}
	} else {
		for (unsigned int i = 0; i < NEOPIXEL_MATRIX_NUM_COLUMNS; i++) {
			for (unsigned int j = 0; j < NEOPIXEL_MATRIX_NUM_ROWS; j++) {
				NeoPixelMatrix.setMatrixPixelColor((i + j) % NEOPIXEL_MATRIX_NUM_COLUMNS, j,
						Wheel(tWheelOffset + (tWheelOffset + (i * (256 / NEOPIXEL_MATRIX_NUM_COLUMNS)))));
			}
		}
	}
	NeoPixelMatrix.show();
	tWheelOffset++; // Wrap around at 256

	delay(20);
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

