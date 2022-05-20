/*
 * Lessons to measure reaction time with 2 buttons and 3 LEDs
 *
 *
 * Copyright 2018 Armin Joachimsmeyer
 * This code is released under GPLv3 license.
 */

/*
 * WICHTIGE TASTENKOMBINATIONEN
 * Formatieren: "strg" + "F"
 * Definition finden: "F3"
 * Autocompletion: "strg" + Leertaste
 * Verwendung suchen: "strg" + "G"
 *
 * Vergleichsoperatoren sind: "==", "!=", ">=", ">=".
 * Bedingungen werden verknüpft mit: "and" / "&&" oder "or" / "||"  und mit "not" / "!" negiert.
 */

#include <Arduino.h>

#include "PlayRtttl.hpp"

#define VERSION "1.0"

#define PIN_GREEN_LED      	2
#define PIN_YELLOW_LED    	3
#define PIN_RED_LED        	4

#define PIN_RIGHT_LED		PIN_GREEN_LED
#define PIN_LEFT_LED     	PIN_RED_LED
#define PIN_START_LED    	PIN_YELLOW_LED

#define PIN_RIGHT_BUTTON   A1
#define PIN_LEFT_BUTTON    A4

#define PIN_LASER	        5
#define PIN_SERVO_HORIZONTAL 6
#define PIN_SERVO_VERTICAL 	7
#define PIN_NEO_PIXEL       8
#define TRIGGER_OUT_PIN     9
#define ECHO_IN_PIN        10
#define PIN_SPEAKER        11
#define PIN_INTERNAL_LED   13

#define PIN_POTENTIOMETER  A0
#define PIN_LDR			   A5

const int POINTS_FOR_WIN = 3;

int sLeftPlayerScore, sRightPlayerScore;

// forward declaration
void blinkLed(int aLedPin, int aNumberOfBlinks, int aBlinkDelay);

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION " from " __DATE__));

	// Enable output on the LED pins
	pinMode(PIN_RED_LED, OUTPUT);
	pinMode(PIN_YELLOW_LED, OUTPUT);
	pinMode(PIN_GREEN_LED, OUTPUT);

	// Prepare for buttons at the pins
	pinMode(PIN_RIGHT_BUTTON, INPUT_PULLUP);
	pinMode(PIN_LEFT_BUTTON, INPUT_PULLUP);
}

/*
 * Die mittlere Led nach einer zufälligen Zeit anschalten und dann warten, welche Taste zuerst gedrückt wird.
 * Die Zeit bis zum Drücken der Taste ausgeben und die Led an der zuerst gedrückten Taste leuchten lassen.
 * Wenn ein Spieler die Punktzahl erreicht hat eine Melodie spielen.
 * Danach kurz warten und die Messung wieder von vorne beginnen.
 */
void loop() {
	int tRightPlayerSwitch;
	int tLeftPlayerSwitch;

	delay(random(500, 4000));

	/*
	 * Task 3. Check for cheating just before switching led on and give feedback if detected
	 * Bestrafe cheaten (der Button ist schon vor dem angehen der LED gedrückt) mit Punktabzug
	 *   und signalisiere das mit einer blinkenden LED.
	 */

	// Switch on start LED
	digitalWrite(PIN_START_LED, HIGH);
	uint32_t tStartMillis = millis();

	/*
	 * Task 1. Wait for press after LED switched on, give LED feedback and output reaction time
	 * Warte bis ein Button gedrückt wird und gebe die Reaktionszeit aus. Schalte die LED des Spielers an und erhöhe die Punkte des Spielers.
	 * 		Benutze digitalRead() und z.B. "sRightPlayerScore++".
	 */
	do {
		//???
	} while (tRightPlayerSwitch != LOW and tLeftPlayerSwitch != LOW);

	if (tRightPlayerSwitch == LOW) {
		// Right switch is low
		//???
		Serial.print("Right player wins with ");
	} else {
		// Left switch must be low here
		//???
		Serial.print("Left player wins with ");
	}
	Serial.print(millis() - tStartMillis);
	Serial.println(" ms");

	/*
	 * Task 2. Check for score level, blink LED and play melody
	 * Wenn der Punktestand POINTS_FOR_WIN erreicht hat, lasse die LED blinken und spiele eine Melodie.
	 *		Benutze blinkLed() und playRtttlBlockingPGM(PIN_SPEAKER, StarWars). Selektiere "StarWars" und drücke Taste F3.
	 */
	if (sRightPlayerScore >= POINTS_FOR_WIN) {
		//???
	} else if (sLeftPlayerScore >= POINTS_FOR_WIN) {
		//???
	}

	// Wait before switching off LEDs
	delay(300);

	// Switching off LEDs
	digitalWrite(PIN_RIGHT_LED, LOW);
	digitalWrite(PIN_START_LED, LOW);
	digitalWrite(PIN_LEFT_LED, LOW);

} // loop end

/*
 * Convenience function for blinking led multiple times
 */
void blinkLed(int aLedPin, int aNumberOfBlinks, int aBlinkDelay) {
	for (int i = 0; i < aNumberOfBlinks; i++) {
		digitalWrite(aLedPin, HIGH);
		delay(aBlinkDelay);
		digitalWrite(aLedPin, LOW);
		delay(aBlinkDelay);
	}
}
