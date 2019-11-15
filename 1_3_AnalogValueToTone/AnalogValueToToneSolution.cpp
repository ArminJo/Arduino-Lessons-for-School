/*
 * Lessons for reading analog values
 * Solution for tasks 1-3
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

// the loop routine runs over and over again forever:
void loop() {

	// read the input on analog pin:
	int tAnalogValue = analogRead(PIN_POTENTIOMETER);
	Serial.print("Eingelesener Wert=");
	Serial.println(tAnalogValue);

	/*
	 * Aufgabe 1. Erzeuge einen Ton dessen Tonhöhe abhängig vom eingelesenen Wert ist.
	 * Benutze tone() wie in 1_Melodie
	 */
	int tFrequency = map(tAnalogValue, 0, 1023, 100, 4000);
	tone(PIN_SPEAKER, tFrequency);

	/*
	 * Schwere Zusatzaufgabe 3. Print bargraph
	 * Gebe den analogen Wert als variabel lange Zeichenkette von z.B. '#' aus.
	 * 		Teile den analogen Wert, so dass Du einen Wert zwischen 0 und 16 bekommst.
	 * 		benutze einen for loop der so oft läuft, wie der errechnete Wert angibt.
	 * 		Benutze Serial.print("#"); im loop.
	 * 		Nach dem loop einmal Serial.println() nicht vergessen.
	 */
	for (int i = 0; i < tAnalogValue / 64; ++i) {
		Serial.print('#');
	}
	Serial.println();

	delay(300);
}

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();

}
