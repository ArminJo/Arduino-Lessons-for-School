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

BlinkLed RedLed(PIN_RED_LED);
BlinkLed YellowLed(PIN_YELLOW_LED);
BlinkLed GreenLed(PIN_GREEN_LED);

void playRandomSongAndBlink();

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();
	initUSDistancePins(PIN_TRIGGER_OUT, PIN_ECHO_IN);

	randomSeed(getUSDistance());
	/*
	 * Play first song
	 */
	playRandomSongAndBlink();
	YellowLed.off(); // switch it manually off here
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
	if (tCentimeter > 40 && tCentimeter < 120) {
		playRandomSongAndBlink();

		// wait for distance to be out of range for 4 consecutive readings
		uint8_t tCounter = 0;
		tCentimeter = getUSDistanceAsCentiMeter();
		while (tCounter < 4) {
			Serial.print("Distance=");
			Serial.print(tCentimeter);
			if (tCentimeter < 40 || tCentimeter > 120) {
				tCounter++;
				Serial.print(" counter=");
				Serial.print(tCounter);
				Serial.println();
			} else {
				tCounter = 0; // reset to start condition
				Serial.print(" still in range. Wait for ");
				Serial.print(4 - tCounter);
				Serial.println(" distances out of range.");
			}
			YellowLed.update();
			tCentimeter = getUSDistanceAsCentiMeter();
			delay(200);
		}
	}
	YellowLed.off();
}

/*
 * Leaves yellow led blinking
 */
void playRandomSongAndBlink() {
	char StringBuffer[16];
	Serial.println();
	Serial.print("Now playing: ");
	startPlayRandomRtttlFromArrayPGM(PIN_SPEAKER, RTTTLChristmasMelodies, ARRAY_SIZE_CHRISTMAS_SONGS, StringBuffer,
			sizeof(StringBuffer));
	Serial.println(StringBuffer);

	/*
	 * Start LEDs blinking
	 */
	RedLed.startWithOnOffTime(300, 600);
	YellowLed.startWithOnOffTime(800, 400);
	GreenLed.startWithOnOffTime(1000, 1500);

// wait for the song to end
	while (updatePlayRtttl()) {
		RedLed.update();
		YellowLed.update();
		GreenLed.update();
		delay(1);
	}
// switch off only 2 leds, the third will blink until the "thing in the right distance" is gone
	RedLed.off();
	GreenLed.off();
	delay(2000);
}
