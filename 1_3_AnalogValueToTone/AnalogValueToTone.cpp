/*
 * Lessons for reading analog values
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

// Die loop Funktion läuft unendlich durch.
void loop() {

	// Einlesen der Werte des Drehreglers
	int tAnalogValue = analogRead(PIN_POTENTIOMETER);
	// Ausgeben des Zahlenwerts
	Serial.print("Eingelesener Wert=");
	Serial.println(tAnalogValue);

	/*
	 * Aufgabe 1. Erzeuge einen Ton dessen Tonhöhe abhängig vom eingelesenen Wert ist.
	 * Benutze tone() wie in 1_Melodie
	 */
//	int tFrequency = map(tAnalogValue, 0, 1023, 100, 4000);

	/*
	 * Aufgabe 2. Lese stattdessen den Spannungswert vom lichtempfindlichen Widerstand am PIN_LDR ein und gebe ihn aus.
	 */

	/*
	 * Schwere Zusatzaufgabe. Print bargraph
	 * Gebe den analogen Wert als variabel lange Zeichenkette von z.B. '#' aus.
	 * 		Teile den analogen Wert, so dass Du einen Wert zwischen 0 und 16 bekommst.
	 * 		benutze einen for loop der so oft läuft, wie der errechnete Wert angibt.
	 * 		Benutze Serial.print("#"); im loop.
	 * 		Nach dem loop einmal Serial.println() nicht vergessen.
	 */

	delay(300);
}

// The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();

}
