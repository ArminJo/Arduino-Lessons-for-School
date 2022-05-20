/*
 * Lesson for using Talkie library
 *
 * Copyright 2018-2022 Armin Joachimsmeyer
 *
 * This code is released under GPLv3 license.
 *
 *  This file is part of Arduino-Lessons-for-School https://github.com/ArminJo/Arduino-Lessons-for-School.
 *
 *  Arduino-Lessons-for-School is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
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
 */

#include <Arduino.h>

#include <Talkie.h>
#include <TalkieUtils.h>

#define VERSION "1.0"

#define PIN_GREEN_LED          2
#define PIN_YELLOW_LED        3
#define PIN_RED_LED            4

#define PIN_RIGHT_LED        PIN_GREEN_LED
#define PIN_LEFT_LED         PIN_RED_LED
#define PIN_START_LED        PIN_YELLOW_LED

#define PIN_RIGHT_BUTTON   A1
#define PIN_LEFT_BUTTON    A4

#define PIN_LASER            5
#define PIN_SERVO_HORIZONTAL 6
#define PIN_SERVO_VERTICAL     7
#define PIN_NEO_PIXEL       8
#define TRIGGER_OUT_PIN     9
#define ECHO_IN_PIN        10
#define PIN_BUZZER        11
#define PIN_INTERNAL_LED   13

#define PIN_POTENTIOMETER  A0
#define PIN_LDR               A5

/*
 * The variable Voice of type Talkie.
 */
Talkie Voice;

//The setup function is called once at startup of the sketch
void setup() {
    // Start serial output
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

    // Prepare for buttons at the pins
    pinMode(PIN_RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(PIN_LEFT_BUTTON, INPUT_PULLUP);

}

// the loop routine runs over and over again forever:
void loop() {
    // read the input on analog pin:
    int tAnalogValue = analogRead(PIN_POTENTIOMETER);
    Serial.print("AnalogValue=");
    Serial.println(tAnalogValue);

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float tVoltage = tAnalogValue * (5.0 / 1023.0);
    Serial.print("Voltage=");
    Serial.println(tVoltage);

    /*
     * Task 4. Spell floating point number
     * Füge die Talkie library zum Projekt hinzu und gebe den Wert von tVoltage damit aus.
     *      Ausgabe dann mit: sayQFloat(&Voice, tVoltage,2).
     *      Warten auf das Ende der Ausgabe mit Voice.wait().
     */
    delay(300);
}
