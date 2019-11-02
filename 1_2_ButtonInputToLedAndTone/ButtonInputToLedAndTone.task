/*
 * Lessons with 2 Buttons 2 LEDs and a speaker or piezo
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
 * Bedingungen werden verknüpft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

#define	DELAY_LOOP			100

// Variablen für Zusatzaufgabe
static int sOldRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
static int sOldLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

// The loop routine runs over and over again forever
void loop() {

	/*
	 * Zusatzaufgabe. Rufe Serial.print nur dann auf, wenn der Zustand des Buttons sich geändert hat.
	 * Vergleiche dazu aktuellen Wert mit altem Wert.
	 */

	/*
	 * Aufgabe 1. Lasse die rechte LED leuchten, solange der rechte Button gedrückt ist.
	 * Lasse die linke LED leuchten, solange der linke Button gedrückt ist.
	 * LOW ist 0 / false, HIGH ist 1 / true
	 */
	// Right button handling
	if (digitalRead(PIN_RIGHT_BUTTON) == 0) {
		Serial.println("RightButton is 0");
		digitalWrite(PIN_RED_LED, HIGH);
	} else {
		Serial.println("RightButton is 1");
	}

	// Left button handling


	/*
	 * Aufgabe 2. Gebe einen Ton von 1760 Hz aus, wenn der rechte Button gedrückt ist.
	 * Gebe einen Ton von 2200 Hz aus, wenn der linke Button gedrückt ist.
	 * Bedingungen weden mit "&&" AND verknüpft
	 *
	 * Zusatz: Gebe 2640 Hz aus, wenn beide Buttons gedrückt sind.
	 */
	if (digitalRead(PIN_RIGHT_BUTTON) == 0 && digitalRead(PIN_LEFT_BUTTON) == 0) {
		tone(PIN_SPEAKER, 2640);
	} else {
		noTone(PIN_SPEAKER);
	}

	// Wait to reduce serial output
	delay(DELAY_LOOP);
}

// The setup function is called once at startup of the program
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();

	// Play 2200 Hz.
	tone(PIN_SPEAKER, 2200);

	// Let LED blink for 600 ms
	digitalWrite(PIN_RED_LED, HIGH);
	digitalWrite(PIN_GREEN_LED, HIGH);
	delay(600);

	// Stop tone
	noTone(PIN_SPEAKER);
	digitalWrite(PIN_RED_LED, LOW);
	digitalWrite(PIN_GREEN_LED, LOW);

}

