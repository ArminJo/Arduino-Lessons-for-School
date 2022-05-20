/*
 * Lessons with 2 buttons 2 LEDs
 * Den Zustand der beiden Buttons einlesen und und auf dem Serial Monitor ausgeben.
 *
 * Thema:
 * - Einlesen digitaler Werte.
 * - if / else Anweisung, logisches invertieren.
 * - Statische Variable.
 *
 *  Copyright 2019-2022 Armin Joachimsmeyer
 *  This code is released under GPLv3 license.
 *
 *  This file is part of Arduino-Lessons-for-School https://github.com/ArminJo/Arduino-Lessons-for-School.
 *
 *  Arduino-Lessons-for-School is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  Copyright 2019-2022 Armin Joachimsmeyer
 *  This code is released under GPLv3 license.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/gpl.html>.
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

#define    DELAY_LOOP            100

// Variablen für Zusatzaufgabe
static int sOldRightButtonValue;
static int sOldLeftButtonValue;

// The loop routine runs over and over again forever
void loop() {

    /*
     * Aufgabe 1. - if / else Anweisung
     *
     * Lasse die rechte LED leuchten, solange der rechte Button gedrückt ist.
     * Lasse die linke LED leuchten, solange der linke Button gedrückt ist.
     * LOW ist 0 / false, HIGH ist 1 / true
     *
     * Aufgabe 2. - logisches invertieren.
     * Geht das auch ohne if / else?
     * LOW ist 0 / false, HIGH ist 1 / true
     *
     */
    // Right button handling
    if (digitalRead(PIN_RIGHT_BUTTON) == 0) {
        digitalWrite(PIN_GREEN_LED, HIGH);
    } else {
        // hier fehlt noch was
    }

    // Left button handling


    int tNewRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
    int tNewLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

    if (tNewRightButtonValue == 0) {
        Serial.println("RightButton is 0");
    } else {
        Serial.println("RightButton is 1");
    }
    // Das ist die einfachere Ausgabemöglichkeit ohne if else
    Serial.print("LeftButton is ");
    Serial.println(tNewLeftButtonValue);

    /*
     * Aufgabe 3. - Statische Variable.
     *
     * Rufe Serial.print nur dann auf, wenn der Zustand des Buttons sich geändert hat.
     * Vergleiche dazu aktuellen Wert mit altem Wert ( z.B. sOldRightButtonValue).
     */
    if (sOldLeftButtonValue != tNewLeftButtonValue) {
        // Ausgabe nur, wenn sich der Wert von tNewLeftButtonValue gegenüber dem letzten loop Durchlauf geändert hat.

    }

    if (sOldRightButtonValue != tNewRightButtonValue) {

    }

    // Wait to reduce serial output
    delay(DELAY_LOOP);
}

// The setup function is called once at startup of the program
void setup() {
    // Start serial output
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();

    // Let LED blink for 600 ms
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_GREEN_LED, HIGH);
    delay(600);

    digitalWrite(PIN_RED_LED, LOW);
    digitalWrite(PIN_GREEN_LED, LOW);

    sOldRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
    sOldLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);
}

