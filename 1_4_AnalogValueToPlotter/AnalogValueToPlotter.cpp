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
 * Vergeichsoperatoren sind: "==", "!=", ">=", "<=".
 * Bedingungen werden verknüpft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

int sLDRMinimum = 1023; // Warum wird das Minimum mit einem so hohen Wert vorbelegt?
int sLDRMaximum = 0;

// Die loop Funktion läuft unendlich durch.
void loop() {

    /*
     * Aufgabe 1.
     *
     * Sieh Dir die Ausgabe einmal im Arduino seriellen Monitor (Strg+Umschalt+M) und einmal im Arduino Plotter (Strg+Umschalt+L) an.
     * Die erste Zeile enthält die Texte für die Legende, alle anderen Zeilen enthalten die mit Space getrennten Werte.
     */
    int tAnalogValuePotentiometer = analogRead(PIN_POTENTIOMETER);
    int tAnalogValueLDR = analogRead(PIN_LDR);

//Ausgabe der ersten 2 Werte
    Serial.print(tAnalogValuePotentiometer);
    Serial.print(' '); // This is only one character, no string!
    Serial.print(tAnalogValueLDR);

    /*
     * Aufgabe 2.
     *
     * Ermittele das Minimum  und das Maximum der eingelesen Werte des LDR's.
     */
    if (tAnalogValueLDR < sLDRMinimum) {
        ;
    }

// Ausgabe des LDR Minimums und Maximums
    Serial.print(' ');
    Serial.print(sLDRMinimum);
    Serial.print(' ');
    Serial.print(sLDRMaximum);

    /*
     * Aufgabe 3.
     *
     * Berechne jetzt zusätzlich das Minimum und Maximum der Werte des Potentiometers und gebe sie aus.
     * Dazu muss:
     * 1. Die Überschrift erweitert werden
     * 2. 2 Variablen für das Minimum und Maximum angelegt werden
     * 3. Die Minimum und Maximum Werte berechnet werden
     * 4. Die Minimum und Maximum Werte ausgegeben werden
     */

    Serial.println(); // End of data set

    delay(100);
}

// The setup function is called once at startup of the sketch
void setup() {
// Start serial output
    Serial.begin(115200);
// Just to know which program is running on my Arduino
//Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();

// Print legend for plotter data
    Serial.println("Potentiometer LDR LDR_Minimum LDR_Maximum");
}
