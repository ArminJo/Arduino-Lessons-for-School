/*
 * Lessons with 3 LEDs in red yellow and green
 * Solution for tasks 1-3
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
 * Vergeichsoperatoren sind: "==", "!=", ">=", ">=".
 * Bedingungen werden verkn�pft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

#define	DELAY_SHORT			700
#define	DELAY_LONG			4000


// the loop routine runs over and over again forever
void loop() {
	digitalWrite(PIN_RED_LED, HIGH);

	/*
	 * Zusatzaufgabe 3.
	 * Wenn es rot ist, lese den rechten und linken Button aus und breche das delay ab, wenn einer gedr�ckt ist.
	 * 		Baue einen for loop von 0 bis 99.
	 * 		Tippe "for" dann Autocomplete dann auf i dr�cken und dann weiter mit der TAB Taste und 100 eingeben.
	 * 		Darin ein delay mit einem 100stel der Zeit von delay(DELAY_LONG).
	 * 		Au�erdem darin auch ein if (digitalRead(PIN_RIGHT_BUTTON)==LOW) { break;}.
	 */
	for (int i = 0; i < 100; ++i) {
		if (digitalRead(PIN_RIGHT_BUTTON) == LOW || digitalRead(PIN_LEFT_BUTTON) == LOW) {
			break;
		}
		delay(DELAY_LONG / 100);
	}

	digitalWrite(PIN_YELLOW_LED, HIGH);
	delay(DELAY_SHORT);

	digitalWrite(PIN_RED_LED, LOW);
	digitalWrite(PIN_YELLOW_LED, LOW);
	digitalWrite(PIN_GREEN_LED, HIGH);

	/*
	 * Aufgabe 2. Gebe 4 mal einen Ton von 440 Hz aus, wenn es gr�n ist.
	 *  	Benutze einen loop um das nicht 4 mal hinschreiben zu m�ssen.
	 */
	for (int i = 0; i < 4; ++i) {
		tone(PIN_SPEAKER, 440, DELAY_LONG / 8);
		delay(DELAY_LONG / 4);
	}

	digitalWrite(PIN_GREEN_LED, LOW);
	digitalWrite(PIN_YELLOW_LED, HIGH);
	delay(DELAY_SHORT);

	digitalWrite(PIN_YELLOW_LED, LOW);

}

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();
}

