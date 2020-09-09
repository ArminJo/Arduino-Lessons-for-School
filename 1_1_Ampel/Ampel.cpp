/*
 * Lesson traffic light with 3 LEDs red, yellow and green
 *
 * Thema:
 * - Ausgabe digitaler Werte auf einem Ardiono Pin.
 * - Warten mit delay().
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
 * Vergleichsoperatoren sind: "==", "!=", ">=", ">=".
 * Bedingungen werden verknüpft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

#define	DELAY_SHORT			700  	// 0,7 Sekunden
#define	DELAY_LONG			3000	// 3 Sekunden

// Die loop Funktion läuft unendlich durch.
void loop() {

	//Rote LED an (HIGH)
	digitalWrite(PIN_RED_LED, HIGH);

	// 3 Sekunden warten
	delay(DELAY_LONG);

	// Gelbe LED auch an
	digitalWrite(PIN_YELLOW_LED, HIGH);

	// kurz warten
	delay(DELAY_SHORT);

	// Rote LED aus
	digitalWrite(PIN_RED_LED, LOW);
	// Gelbe LED aus, grüne LED an

	/*
	 * Aufgabe 1. Programmiere die fehlenden Ampelphasen grün und gelb.
	 */

	/*
	 * Aufgabe 2. Wenn es grün ist: Statt einmal mit "delay(DELAY_LONG_MS);" zu warten, warte 4 mal und gebe jedesmal einen Ton von 440 Hz aus.
	 * 		Benutze einen loop um das nicht 4 mal hinschreiben zu müssen.
	 */
//	tone(PIN_SPEAKER, 440, DELAY_LONG / 8);
//	delay(DELAY_LONG / 4);

	/*
	 * Zusatzaufgabe 3.
	 * Wenn es rot ist, lese den rechten und linken Button aus und breche das delay ab, wenn einer gedrückt ist.
	 * 		Baue einen for loop von 0 bis 99.
	 * 		Tippe "for" dann Autocomplete dann auf i drücken und dann weiter mit der TAB Taste und 100 eingeben.
	 * 		Darin ein delay mit einem 100stel der Zeit von delay(DELAY_LONG).
	 * 		Außerdem darin auch ein if (digitalRead(PIN_RIGHT_BUTTON)==LOW) { break;}.
	 */

}

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();
}

