/*
 * Lesson playing Christmas melody if US Sensor value is a defined range.
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
 */

#include <Arduino.h>
#include "Breadboard.h"

#include "HCSR04.h"
#include "BlinkLed.h"
#include <PlayRtttl.h>

#define VERSION_EXAMPLE "1.0"

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();
	initUSDistancePins(PIN_TRIGGER_OUT, PIN_ECHO_IN);
}

/*
 * Aufgabe: 1. Verändere die Bedingung so, dass die Melodie nur dann abgespielt wird, wenn die Entfernung zwischen 2 Werten liegt.
 * 					Zwei Bedingungen werden mit && "UND" verknüpft.
 * 			2. Benutze die random() Funktion um ein zufälliges Lied abzuspielen.
 * 			3. Warte solange bis eine Messung ausserhalb der obigen 2 Werte liegt, um zu vermeiden, dass andauernd Melodien gespielt werden.
 */
void loop() {
	unsigned int tCentimeter = getUSDistanceAsCentiMeter();
	Serial.print("Distance=");
	Serial.println(tCentimeter);
	delay(100);
	if (tCentimeter < 60) {
		int tIndexOfSong = random(ARRAY_SIZE_CHRISTMAS_SONGS);
		playRtttlBlockingPGM(PIN_SPEAKER, RTTTLChristmasMelodies[2]);
		delay(2000);
	}
}
