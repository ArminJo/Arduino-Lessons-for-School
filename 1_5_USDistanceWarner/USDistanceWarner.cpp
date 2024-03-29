/*
 * Lessons for reading HC-SR04 US Sensor and generating tones from a pentatonic scale.
 *
 * Thema:
 * - Datenblatt eines Abstandsmessers lesen und ihn richtig ansteuern.
 * - Ultraschall Abstandssensor einlesen.
 * - Laufzeit des Schalls in Abstand umrechnen.
 * - Leuchtdioden und Lautsprecher ansteuern
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
 * Bedingungen werden verkn�pft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>
#include "Breadboard.h"

#define VERSION_EXAMPLE "1.0"

// Die loop Funktion l�uft unendlich durch.
void loop() {

    /*
     * Aufgabe 1.
     *
     * Sieh Dir das Datenblatt des Ultraschall Entfernungsmessers an.
     * Wandele den R�ckgabewert in Centimeter um.
     * Speed of sound at 20 degree is 343,46 m/s.
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
    Serial.print(" Abstand ist:");
    Serial.print(tUSCentimeter);
    Serial.print(" cm");
    Serial.println();

    /*
     * Aufgabe 2.
     * Lasse bei einem Abstand < 10 cm die rote, bei einem Abstand >= 10 und kleiner 30 cm die gelbe und sonst die gr�ne LED leuchten.
     * Unter einem Mindestabstand erzeuge zus�tzlich einen (intermittierenden) Ton.
     */
    if (tUSCentimeter < 10) {
        digitalWrite(PIN_RED_LED, HIGH);
    } else {
        digitalWrite(PIN_RED_LED, LOW);
    }

    if (tUSCentimeter >= 10 && tUSCentimeter < 30) {
        ;
    } else {
        ;
    }

//tone(PIN_BUZZER, 2200);
    delay(200); // Delay to make is easier to play a melody
}

// The setup function is called once at startup of the sketch
void setup() {
// Start serial output
    Serial.begin(115200);
// Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();

    digitalWrite(PIN_GREEN_LED, HIGH);
    delay(300);
    digitalWrite(PIN_GREEN_LED, LOW);

    digitalWrite(PIN_YELLOW_LED, HIGH);
    delay(300);
    digitalWrite(PIN_YELLOW_LED, LOW);

    digitalWrite(PIN_RED_LED, HIGH);
    delay(300);
    digitalWrite(PIN_RED_LED, LOW);

    tone(PIN_BUZZER, 2200);
    delay(500);
    noTone(PIN_BUZZER);
}
