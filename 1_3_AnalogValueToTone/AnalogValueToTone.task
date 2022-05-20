/*
 * Lessons for reading analog values
 * Einen Spannungswert, der durch ein Potentiometer oder einen lichtempfindlichen Widerstand (LDR) erzeugt wird, einlesen und in eine Tonhöhe verwandeln.
 *
 * Thema:
 * - Potentiometer, LDR/Lichtwiderstand.
 * - Einlesen analoger Werte.
 * - map() Funktion.
 * - Verwendung von Variablen in der Loopdefinition.
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
 * Vergleichsoperatoren sind: "==", "!=", ">=", "<=".
 * Bedingungen werden verknüpft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

// Die loop Funktion läuft unendlich durch.
void loop() {

    /*
     *  Aufgabe 1. - Übersetzen, hochladen und im Serial Monitor ansehen.
     *
     *  Einlesen der Werte des Drehreglers (oder des LDR's)
     *  Welche Werte liefert analogRead()?
     */
    int tAnalogValue = analogRead(PIN_POTENTIOMETER); // oder PIN_LDR
// Ausgeben des Zahlenwerts
    Serial.print("Eingelesener Wert=");
    Serial.println(tAnalogValue);

    /*
     * Aufgabe 2. - Umwandeln des eingelesenen Werts in einen Ton.
     *
     * Erzeuge einen Ton mit "tone()" dessen Tonhöhe abhängig vom eingelesenen Wert des Potentiometers ist.
     * Mit "map()" werden Werte aus einem Bereich in einen anderen transformiert.
     *
     * Aufgabe 3. - LDR/Lichtwiderstand statt Potentiometer einlesen.
     *
     * Lese statt des Potentiometers den Spannungswert am lichtempfindlichen Widerstand am PIN_LDR ein und gebe ihn aus.
     * Welche Werte bekomme ich da?
     * Wie muss ich map() ändern, um den vollen Tonumfang zu erreichen?
     */
//int tFrequency = map(tAnalogValue, ???, ???, 440, 1760); // 2 octaves
//tone(PIN_BUZZER, 2200);
    delay(200);
}

// The setup function is called once at startup of the sketch
void setup() {
// Start serial output
    Serial.begin(115200);
// Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();

// Play 2200 Hz for 600 milliseconds.
    tone(PIN_BUZZER, 2200, 600);
}
