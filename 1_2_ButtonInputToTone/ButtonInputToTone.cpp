/*
 * Lessons with 2 buttons 2 LEDs and a speaker or piezo
 * Den Zustand der beiden Buttons einlesen und je nach gedr�ckten Buttons verschiedene T�ne ausgeben.
 *
 * Thema:
 * - Ausgabe eines Tons.
 * - Verkn�pfung von Bedingungen.
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

#define    DELAY_LOOP            100

void handleLedAndSerial();

// The loop routine runs over and over again forever
void loop() {

    handleLedAndSerial();
    uint8_t tRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
    uint8_t tLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

    /*
     * Aufgabe 1. Verkn�pfung von Bedingungen:
     *
     * Gebe einen Ton von 1760 Hz aus, wenn nur der rechte Button gedr�ckt ist.
     * Gebe einen Ton von 2200 Hz aus, wenn nur der linke Button gedr�ckt ist.
     * Gebe 2640 Hz aus, wenn beide Buttons gedr�ckt sind.
     *
     * Was ist der Unterschied zwischen der Verwendung von tRightButtonValue und digitalRead(PIN_RIGHT_BUTTON)?
     * Wann ist was besser?
     *
     * Bedingungen weden mit "&&" AND verkn�pft
     */
    if (tRightButtonValue == 0 && tLeftButtonValue == 1) {
        // Wenn nur der rechte Button gedr�ckt ist
        tone(PIN_BUZZER, 1760);
//    } else if () {
        // Wenn nur der linke Button gedr�ckt ist
//    } else if () {
        // Wenn beide Buttons gedr�ckt sind
    } else { // Warum darf hier das "if" fehlen?
        // Wenn kein Button gedr�ckt ist
        noTone(PIN_BUZZER);
    }

    // Wait to reduce serial output
    delay(DELAY_LOOP);
}

void handleLedAndSerial() {
    static int sOldRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
    static int sOldLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

    int tNewRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
    int tNewLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

    digitalWrite(PIN_RED_LED, !tNewRightButtonValue);
    digitalWrite(PIN_GREEN_LED, !tNewLeftButtonValue);
    if (sOldRightButtonValue != tNewRightButtonValue) {
        sOldRightButtonValue = tNewRightButtonValue;
        Serial.print("RightButton is ");
        Serial.println(tNewRightButtonValue);
    }
    if (sOldLeftButtonValue != tNewLeftButtonValue) {
        sOldLeftButtonValue = tNewLeftButtonValue;
        Serial.print("LeftButton is ");
        Serial.println(tNewLeftButtonValue);
    }
}

// The setup function is called once at startup of the program
void setup() {
    // Start serial output
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();

    // Play 2200 Hz.
    tone(PIN_BUZZER, 2200);

    // Let LED blink for 600 ms
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_GREEN_LED, HIGH);
    delay(600);

    // Stop tone
    noTone(PIN_BUZZER);
    digitalWrite(PIN_RED_LED, LOW);
    digitalWrite(PIN_GREEN_LED, LOW);
}

