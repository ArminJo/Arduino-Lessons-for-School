/*
 * Lessons for reading analog values
 *
 * Thema:
 * - Potentiometer, LDR/Lichtwiderstand.
 * - Einlesen analoger Werte.
 * - map() Funktion.
 * - Verwendung von Variablen in der Loopdefinition.
 * - Arduino Plotter.
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

// Die loop Funktion läuft unendlich durch.
void loop() {

	// Einlesen der Werte des Drehreglers
	int tAnalogValue = analogRead(PIN_POTENTIOMETER); // oder PIN_LDR
	// Ausgeben des Zahlenwerts
	Serial.print("Eingelesener Wert=");
	Serial.println(tAnalogValue);

	/*
	 * Aufgabe 1. - Potentiometer, Einlesen analoger Werte, map() Funktion.
	 *
	 * Erzeuge einen Ton mit "tone()" dessen Tonhöhe abhängig vom eingelesenen Wert des Potentiometers ist.
	 * Mit "map()" werden Werte aus einem Bereich in einen anderen transformiert.
	 */
//	int tFrequency = map(tAnalogValue, 0, 1023, 100, 4000);

	/*
	 * Aufgabe 2. - LDR/Lichtwiderstand
	 *
	 * Lese stattdessen den Spannungswert vom lichtempfindlichen Widerstand am PIN_LDR ein und gebe ihn aus.
	 * Wie sieht die Ausagabe im Arduino Plotter aus?
	 */

	/*
	 * Aufgabe 3. - Arduino Plotter
	 *
	 * Gebe beide Werte für den Arduino Plotter aus
	 * 	Die erste Zeile enthält die Texte für die Legende
	 * 	Alle anderen Zeilen enthalten die mit Space getrennten Werte.
	 */

	/*
	 * Schwere Zusatzaufgabe für die Pro's. Print bargraph - Verwendung von Variablen in der Loopdefinition
	 *
	 * Gebe den analogen Wert als variabel lange Zeichenkette von '#' aus.
	 * Für die Werte 16 bis 31 gebe "#" aus, für die Werte 32 bis 47 "##",
	 * ... für Werte von 240 bis 255 "###############" (15 '#').
	 *
	 * Anleitung:
	 * 		Teile den analogen Wert, so dass Du einen Wert zwischen 0 und 15 bekommst.
	 * 		benutze einen for loop der so oft läuft, wie der errechnete Wert angibt.
	 * 		Benutze Serial.print('#'); im loop.
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
