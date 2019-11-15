/*
 * Lessons with 2 buttons 2 LEDs and a speaker or piezo
 *
 * Thema:
 * - if / else Anweisung, logisches invertieren.
 * - Statische Variable.
 *
 *  Copyright 2019 Armin Joachimsmeyer
 *  This code is released under GPLv3 license.
 *
 *  This file is part of Arduino-Lessons-for-School https://github.com/ArminJo/Arduino-Lessons-for-School.
 *
 *  Arduino-Lessons-for-School is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
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
	 * Aufgabe 1. - if / else Anweisung, logisches invertieren.
	 *
	 * Lasse die rechte LED leuchten, solange der rechte Button gedrückt ist.
	 * Lasse die linke LED leuchten, solange der linke Button gedrückt ist.
	 * LOW ist 0 / false, HIGH ist 1 / true
	 */
	// Right button handling
	if (digitalRead(PIN_RIGHT_BUTTON) == 0) {
		digitalWrite(PIN_RED_LED, HIGH);
	} else {
		// hier fehlt noch was
	}

	// Left button handling

	/*
	 * Aufgabe 2. - Statische Variable.
	 *
	 * Rufe Serial.print nur dann auf, wenn der Zustand des Buttons sich geändert hat.
	 * Vergleiche dazu aktuellen Wert mit altem Wert ( z.B. sOldRightButtonValue).
	 */
	int tNewRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
	int tNewLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

	if (tNewRightButtonValue == 0) {
		Serial.println("RightButton is 0");
	} else {
		Serial.println("RightButton is 1");
	}

	if (sOldLeftButtonValue != tNewLeftButtonValue) {
		// Das ist die einfachere Ausgabemöglichkeit
		Serial.print("LeftButton is ");
		Serial.println(tNewLeftButtonValue);
		// Was fehlt hier?
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

