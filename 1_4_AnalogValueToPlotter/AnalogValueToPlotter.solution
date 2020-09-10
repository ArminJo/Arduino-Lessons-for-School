/*
 * Lessons for printing analog values on the Arduino Plotter
 *
 * Thema:
 * - Potentiometer, LDR/Lichtwiderstand.
 * - Einlesen analoger Werte.
 * - Arduino Plotter.
 * - Minimum / Maximum finden.
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
	static int sLDRMinimum = 1023;
	static int sLDRMaximum = 0;
	/*
	 * Aufgabe 1.
	 *
	 * Sieh Dir die Ausgabe einmal im Arduino seriellen Monitor (Strg+Umschalt+M) und einmal im Arduino Plotter (Strg+Umschalt+L) an.
	 * Die erste Zeile enthält die Texte für die Legende, alle anderen Zeilen enthalten die mit Space getrennten Werte.
	 */
	int tAnalogValuePotentiometer = analogRead(PIN_POTENTIOMETER);
	int tAnalogValueLDR = analogRead(PIN_LDR);
	Serial.print(tAnalogValuePotentiometer);
	Serial.print(' '); // This is only one character, no string!
	Serial.print(tAnalogValueLDR);

	/*
	 * Aufgabe 2.
	 *
	 * Compute the minimum and maximum of the LDR readout values.
	 * Ermittele das Minimum  und das Maximum der eingelesen Werte des LDR's.
	 */
	if (sLDRMinimum > tAnalogValueLDR) {
		sLDRMinimum = tAnalogValueLDR;
	}
	if (sLDRMaximum < tAnalogValueLDR) {
		sLDRMaximum = tAnalogValueLDR;
	}

	Serial.print(' ');
	Serial.print(sLDRMinimum);
	Serial.print(' ');
	Serial.print(sLDRMaximum);
	Serial.println(); // End of data set



	/*
	 * Aufgabe 3.
	 *
	 * Verbessere mit Hilfe des Minimums und Maximums den ausgegebenen Frequenzbereich des LDR Wertes,
	 * der vorher nicht 2 Oktaven war wie beim Potentiometer.
	 * Ermittele das Minimum  und das Maximum der eingelesen Werte des LDR's.
	 */
	int tFrequency = map(tAnalogValueLDR, sLDRMinimum, sLDRMaximum, 440, 1760); // 2 octaves
	tone(PIN_SPEAKER, tFrequency);

	delay(300);
}

// The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
//	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();

	// Print legend for plotter data
	Serial.println("Potentiometer LDR Minimum Maximum");
}
