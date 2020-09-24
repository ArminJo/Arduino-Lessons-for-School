/*
 * Lessons for reading HC-SR04 US Sensor and generating tones from a pentatonic scale.
 *
 * Thema:
 * - Datenblatt eines Abstandsmessers lesen und ihn richtig ansteuern.
 * - Ultraschall Abstandssensor einlesen.
 * - Laufzeit des Schalls in Abstand umrechnen.
 * - Werte aus Array holen.
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

// Die loop Funktion läuft unendlich durch.
void loop() {

    /*
     * Aufgabe 1.
     *
     * Sieh Dir das Datenblatt des Ultraschall Entfernungsmessers an.
     * Wandele den Rückgabewert in Centimeter um.
     */
    // need minimum 10 usec Trigger Pulse
    digitalWrite(PIN_TRIGGER_OUT, HIGH);
    delayMicroseconds(10);
    // falling edge starts measurement
    digitalWrite(PIN_TRIGGER_OUT, LOW);

    unsigned long tUSPulseMicros = pulseInLong(PIN_ECHO_IN, HIGH, 20000);
    uint8_t tUSCentimeter = 0;
    Serial.print("Eingelesener Wert ist:");
    Serial.print(tUSPulseMicros);
    Serial.println();

    /*
     * Aufgabe 2.
     *
     * Wandele den Abstand in eine Frequenz um, die du aus dem Array NoteC5ToC7Pentatonic holst.
     * das Array hat ARRAY_SIZE_NOTE_C5_TO_C7_PENTATONIC Einträge.
     *
     */
    uint8_t tIndex = map(tUSCentimeter, 0, 50, 0, ARRAY_SIZE_NOTE_C5_TO_C7_PENTATONIC - 1);

//    tone(PIN_SPEAKER, NoteC5ToC7Pentatonic[0]); // Den richtigen Ton der Tonleiter ausgeben
    delay(200); // Delay to make is easier to play a melody
}

// The setup function is called once at startup of the sketch
void setup() {
    // Start serial output
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();
    for (uint8_t i = 0; i < ARRAY_SIZE_NOTE_C5_TO_C7_PENTATONIC - 1; ++i) {
        tone(PIN_SPEAKER, NoteC5ToC7Pentatonic[i]);
        delay(500);
    }
}
