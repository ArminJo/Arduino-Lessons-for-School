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
 * Bedingungen werden verkn�pft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

#define	DELAY_LOOP			100

// The loop routine runs over and over again forever
void loop() {
	// Variablen f�r Zusatzaufgabe
	static int sOldRightButtonValue = 5;
	static int sOldLeftButtonValue = 5;

	/*
	 * Zusatzaufgabe. Rufe Serial.print nur dann auf, wenn der Zustand des Buttons sich ge�ndert hat.
	 */
	Serial.print("RightButton is ");
	Serial.println(digitalRead(PIN_RIGHT_BUTTON));
	Serial.print("LeftButton is ");
	Serial.println(digitalRead(PIN_LEFT_BUTTON));

	/*
	 * Aufgabe 1. Lasse die rechte LED leuchten, solange der rechte Button gedr�ckt ist.
	 * Lasse die linke LED leuchten, solange der linke Button gedr�ckt ist.
	 * 		Siehe auch letzes Statement unten in setup().
	 */

	/*
	 * Aufgabe 2. Gebe einen Ton von 1760 Hz aus, wenn der rechte Button gedr�ckt ist.
	 * Gebe einen Ton von 2200 Hz aus, wenn der linke Button gedr�ckt ist.
	 * 		Siehe auch letzes Statement unten in setup().
	 * Zusatz: Gebe 2640 Hz aus, wenn beide Buttons gedr�ckt sind.
	 */
	if (false) {
		tone(PIN_SPEAKER, 1000, DELAY_LOOP);
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

	// Play 2200 Hz for 600 ms.
	tone(PIN_SPEAKER, 2200, 600);

	// Let LED blink for 600 ms
	digitalWrite(PIN_RED_LED, HIGH);
	delay(600);
	digitalWrite(PIN_RED_LED, LOW);

}
