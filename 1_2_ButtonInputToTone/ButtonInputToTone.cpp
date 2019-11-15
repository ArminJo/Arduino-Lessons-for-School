/*
 * Lessons with 2 buttons 2 LEDs and a speaker or piezo
 *
 * Thema:
 * - Verknüpfung von Bedingungen
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

#define	DELAY_LOOP			100

void handleLedAndSerial();

// The loop routine runs over and over again forever
void loop() {

	handleLedAndSerial();
	uint8_t tRightButtonValue = digitalRead(PIN_RIGHT_BUTTON);
	uint8_t tLeftButtonValue = digitalRead(PIN_LEFT_BUTTON);

	/*
	 * Aufgabe 1. Verknüpfung von Bedingungen:
	 *
	 * Gebe einen Ton von 1760 Hz aus, wenn nur der rechte Button gedrückt ist.
	 * Gebe einen Ton von 2200 Hz aus, wenn nur der linke Button gedrückt ist.
	 * Gebe 2640 Hz aus, wenn beide Buttons gedrückt sind.
	 *
	 * Was ist der Unterschied zwischen der Verwendung von tRightButtonValue und digitalRead(PIN_RIGHT_BUTTON)?
	 * Wann ist was besser?
	 *
	 * Bedingungen weden mit "&&" AND verknüpft
	 */
	if (tRightButtonValue == 0 && digitalRead(PIN_LEFT_BUTTON) == 1) {
		tone(PIN_SPEAKER, 1760);
	} else {
		noTone(PIN_SPEAKER);
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
	tone(PIN_SPEAKER, 2200);

	// Let LED blink for 600 ms
	digitalWrite(PIN_RED_LED, HIGH);
	digitalWrite(PIN_GREEN_LED, HIGH);
	delay(600);

	// Stop tone
	noTone(PIN_SPEAKER);
	digitalWrite(PIN_RED_LED, LOW);
	digitalWrite(PIN_GREEN_LED, LOW);

}

