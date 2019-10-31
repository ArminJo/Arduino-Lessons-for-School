/*
 * Erzeuge eine Melodie
 *
 * Copyright 2019 Armin Joachimsmeyer
 * This code is released under GPLv3 license.
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

#include "pitches.h"

#define VERSION_EXAMPLE "1.0"

// notes in the start melody:
int MelodyShort[] = {
NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
// note durations: 4 = quarter note, 8 = eighth note, etc.:
uint8_t MelodyShortNoteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

int MelodyAlleMeineEntchen[] = {
NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4,
NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4 };
uint8_t MelodyAlleMeineEntchenNoteDurations[] = { 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 1 };

#define	DELAY_SHORT			700  	// 0,7 Sekunden
#define	DELAY_LONG			3000	// 3 Sekunden

// Die loop Funktion läuft unendlich durch.
void loop() {

	/*
	 * Eine Schleife für die erste Melodie
	 * sizeof() wird ersetzt durch die Anzahl der Bytes im Array, so dass man nicht selber zählen muss
	 */
	for (unsigned int tNoteIndex = 0; tNoteIndex < sizeof(MelodyShortNoteDurations); tNoteIndex++) {
		/*
		 * Ausgabe der Werte, die in dem Array sind
		 */
		Serial.print("Spiele einen Ton mit Tonhöhe ");
		Serial.print(MelodyShort[tNoteIndex]);
		Serial.print(" und Dauer ");
		Serial.print(1000 / MelodyShortNoteDurations[tNoteIndex]);
		// Warte bis der Ton zu Ende ist und ein bischen (0.3 mal) länger
		Serial.print("ms und warte danach ");
		Serial.print(300 / MelodyShortNoteDurations[tNoteIndex]);
		Serial.println(" Millisekunden");

		// to calculate the note duration, take one second divided by the note type.
		// e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		int tNoteDuration = 1000 / MelodyShortNoteDurations[tNoteIndex];
		tone(PIN_SPEAKER, MelodyShort[tNoteIndex], tNoteDuration);

		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		int tPauseBetweenNotes = tNoteDuration * 1.30;
		delay(tPauseBetweenNotes);
	}

	// Pause nach der Melodie, bevor es weitergeht
	delay(5000);

	/*
	 * Und eine Schleife für die zweite Melodie
	 * Das ist übrigens die exakte Notation für sizeof, wenn es sich nicht um ein Array aus Bytes handelt
	 */
	for (unsigned int tNoteIndex = 0; tNoteIndex < (sizeof(MelodyAlleMeineEntchen) / sizeof(MelodyAlleMeineEntchen[0]));
			tNoteIndex++) {

		/*
		 * Ausgabe der Werte, die in dem Array sind
		 */
		Serial.print("Spiele einen Ton mit Tonhöhe ");
		Serial.print(MelodyAlleMeineEntchen[tNoteIndex]);
		Serial.print(" und Dauer ");
		Serial.print(1000 / MelodyAlleMeineEntchenNoteDurations[tNoteIndex]);
		// Warte bis der Ton zu Ende ist und ein bischen (0.3 mal) länger
		Serial.print("ms und warte danach ");
		Serial.print(300 / MelodyAlleMeineEntchenNoteDurations[tNoteIndex]);
		Serial.println(" Millisekunden");

		// to calculate the note duration, take one second divided by the note type.
		// e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
		int tNoteDuration = 1000 / MelodyAlleMeineEntchenNoteDurations[tNoteIndex];
		tone(PIN_SPEAKER, MelodyAlleMeineEntchen[tNoteIndex], tNoteDuration);

		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		int tPauseBetweenNotes = tNoteDuration * 1.30;
		delay(tPauseBetweenNotes);
	}

	// Pause nach der Melodie, bevor es weitergeht
	delay(5000);

}

//The setup function is called once at startup of the sketch
void setup() {
	// Start serial output
	Serial.begin(115200);
	// Just to know which program is running on my Arduino
	Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

	initBreadboardPins();
}

