/*
 * Lessons with 2 Buttons 2 LEDs and a speaker or piezo
 * Solution
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

#define VERSION "1.0"

#include "Breadboard.h"

#define	DELAY_LOOP			100

// The loop routine runs over and over again forever
void loop() {
	// Variablen für Zusatzaufgabe
	// Sie werden hier am Anfang auf einen Wert gesetzt, der nie von digitalRead() geliefert wird,
	// damit der Button Startwert immer einmal angezeigt wird.
	static int sOldRightButtonValue = 5;
	static int sOldLeftButtonValue = 5;

	/*
	 * Zusatzaufgabe. Rufe Serial.print nur dann auf, wenn der Zustand des Buttons sich geändert hat.
	 */
	int tNewRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
	int tNewLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);
	if (sOldRightButtonValue != tNewRightButtonValue) {
		sOldRightButtonValue = tNewRightButtonValue;
		Serial.print("RightButton is ");
		Serial.println(tNewRightButtonValue);
	}
	if (sOldLeftButtonValue != tNewLeftButtonValue) {
		sOldLeftButtonValue = tNewLeftButtonValue;
		Serial.print("LeftButton is ");
		Serial.println(tNewLeftButtonValue);
	}

	/*
	 * Aufgabe 1. Lasse die rechte LED leuchten, solange der rechte Button gedrückt ist.
	 * Lasse die linke LED leuchten, solange der linke Button gedrückt ist.
	 *
	 * Aufgabe 2. Gebe einen Ton von 1760 Hz aus, wenn der rechte Button gedrückt ist.
	 * Gebe einen Ton von 2200 Hz aus, wenn der linke Button gedrückt ist.
	 * 		Siehe auch letzes Statement unten in setup().
	 */
	digitalWrite(PIN_GREEN_LED, LOW);
	digitalWrite(PIN_RED_LED, LOW);

	if (digitalRead(PIN_RIGHT_BUTTON) == LOW) {
		digitalWrite(PIN_GREEN_LED, HIGH);
		tone(PIN_SPEAKER, 1760, DELAY_LOOP);
	}
	if (digitalRead(PIN_LEFT_BUTTON) == LOW) {
		tone(PIN_SPEAKER, 2200, DELAY_LOOP);
		digitalWrite(PIN_RED_LED, HIGH);
	}

	/*
	 * Zusatz: Gebe 2640 Hz aus, wenn beide Buttons gedrückt sind.
	 */
	if (digitalRead(PIN_RIGHT_BUTTON) == LOW && digitalRead(PIN_LEFT_BUTTON) == LOW) {
		tone(PIN_SPEAKER, 2640, DELAY_LOOP);
	}

	// Wait for end of tone()
	delay(DELAY_LOOP);
}

// The setup function is called once at startup of the program
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

	initBreadboardPins();

	// Play 2200 Hz for 600 ms.
	tone(PIN_SPEAKER, 2200, 600);

	// Let LED blink for 600 ms
	digitalWrite(PIN_RED_LED, HIGH);
	delay(600);
	digitalWrite(PIN_RED_LED, LOW);
}

