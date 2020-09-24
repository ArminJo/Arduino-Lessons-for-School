/*
 * Lesson playing Christmas melody if US Sensor value is a defined range.
 *
 * Thema:
 * - Ultraschall Abstandssensor einlesen.
 * - Eine Library benutzen, um Weichnachstlieder abzuspielen.
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
 */

#include <Arduino.h>
#include "Breadboard.h"

#include "HCSR04.h"
#include "BlinkLed.h"
#include <PlayRtttl.h>

#define VERSION_EXAMPLE "1.0"

BlinkLed RedLed(PIN_RED_LED);
BlinkLed YellowLed(PIN_YELLOW_LED);
BlinkLed GreenLed(PIN_GREEN_LED);

//The setup function is called once at startup of the sketch
void setup() {
    // Start serial output
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    initBreadboardPins();
    initUSDistancePins(PIN_TRIGGER_OUT, PIN_ECHO_IN);

    randomSeed(getUSDistance());
    delay(500); // to avoid sound directly at power up
}

/*
 * Aufgabe: 1. Verändere die Bedingung so, dass die Melodie nur dann abgespielt wird, wenn die Entfernung zwischen 2 Werten liegt.
 *             Zwei Bedingungen werden mit && "UND" verknüpft.
 *          2. Benutze die random() Funktion um ein zufälliges Lied abzuspielen.
 *          3. Warte solange bis eine Messung ausserhalb der obigen 2 Werte liegt, um zu vermeiden, dass andauernd Melodien gespielt werden.
 */
void loop() {
    unsigned int tCentimeter = getUSDistanceAsCentiMeter();
    Serial.print("Distance=");
    Serial.println(tCentimeter);
    delay(100);
    if (tCentimeter < 60) {
        int tIndexOfSong = random(ARRAY_SIZE_CHRISTMAS_MELODIES);
        playRtttlBlockingPGM(PIN_SPEAKER, RTTTLChristmasMelodies[2]);
        delay(2000);
    }
}
