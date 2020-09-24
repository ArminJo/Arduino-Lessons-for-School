/*
 * Play a melody
 * Spiele eine Melodie
 *
 * Thema:
 * - Arrays und Loops über Arrays.
 * - sizeof() Funktion.
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

#include "pitches.h"

#define VERSION_EXAMPLE "1.0"

// notes in the start melody:
int MelodyShort[8] = {
NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
// note durations: 4 = quarter note, 8 = eighth note, etc.:
uint8_t MelodyShortNoteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

int MelodyAlleMeineEntchen[] = {
NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4,
NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4 };
uint8_t MelodyAlleMeineEntchenNoteDurations[] = { 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 1 };

#define    DELAY_SHORT            700    // 0,7 Sekunden
#define    DELAY_LONG            3000    // 3 Sekunden

// Die loop Funktion läuft unendlich durch.
void loop() {

    // Spiele den ersten Ton
    /*
     * Ausgabe der Werte, die in dem Array sind
     */
    Serial.print("Spiele einen Ton mit Tonhöhe ");
    Serial.print(MelodyShort[0]);
    Serial.print(" und Dauer ");
    Serial.print(1000 / MelodyShortNoteDurations[0]);
    // Warte bis der Ton zu Ende ist und ein bischen (0.3 mal) länger
    Serial.print("ms und warte danach ");
    Serial.print(300 / MelodyShortNoteDurations[0]);
    Serial.println(" Millisekunden");

    tone(PIN_SPEAKER, MelodyShort[0], 1000 / MelodyShortNoteDurations[0]);
    // Warte bis der Ton zu Ende ist und ein bischen (0.3 mal) länger
    delay(1300 / MelodyShortNoteDurations[0]);

    // Spiele den zweiten Ton
    tone(PIN_SPEAKER, MelodyShort[1], 1000 / MelodyShortNoteDurations[1]);
    delay(1300 / MelodyShortNoteDurations[1]);

    // Spiele den dritten Ton
    tone(PIN_SPEAKER, MelodyShort[2], 1000 / MelodyShortNoteDurations[2]);
    delay(1300 / MelodyShortNoteDurations[2]);

    /*
     * Aufgabe 1. - Arrays + Loops
     *
     * Gebe alle 8 Töne mit den richtigen delays aus.
     * Baue einen Loop mit for, der den Programmcode vereinfacht.
     * Benutze "for (int i = 0; i < 8; ++i) {"
     */

    // Pause nach der Melodie, bevor es weitergeht
    delay(5000);

    /*
     * Aufgabe 2. - sizeof() Funktion
     *
     * Gebe die 2. Melodie aus.
     * Die Länge eines Arrays in Byte ist: sizeof(MelodyAlleMeineEntchen)
     * Die Anzahl der Einträge  Arrays ist: sizeof(MelodyAlleMeineEntchen) / sizeof(MelodyAlleMeineEntchen[0])
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

