/*
 * Lessons with 16 LEDs NeoPixel bar
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

#include <Adafruit_NeoPixel.h>
#include <math.h>

#define VERSION_EXAMPLE "1.0"

// How many NeoPixels are mounted on the bar?
#define NUM_PIXELS      16

// Forward declarations
uint32_t Wheel(uint8_t WheelPos);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel MyNeoPixelBar = Adafruit_NeoPixel(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

//The setup function is called once at startup of the sketch
void setup() {
    // Start serial output
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));
    initBreadboardPins();

    MyNeoPixelBar.begin(); // This initializes the NeoPixel library.

    /*
     * Setze alle Pixel auf rot. Die Parameter der color Funktion bedeuten: Color(<rot>, <gr�n>, <blau>)
     */
    uint8_t tValue = 255;

    for (unsigned int i = 0; i < NUM_PIXELS; i++) {
        Serial.print("Value=");
        Serial.println(tValue);
        MyNeoPixelBar.setPixelColor(i, MyNeoPixelBar.Color(tValue, 0, 0)); // Red
    }
    MyNeoPixelBar.show();
    delay(4000);

    /*
     * Aufgabe 1. Setze alle Pixel auf eine andere Farbe
     */

    /*
     * Aufgabe 2. Steigere die Helligkeit kontinuierlich, indem Du tValue beim ersten Pixel auf 1 setzt
     * und f�r jedes weiter Pixel einen konstanten Wert addierst.
     * Wie ist die Formel f�r den konstanten Wert, wenn ich 16 Werte von 1 bis 255 haben will?
     *
     * Hast Du eine Idee warum das nicht gleichm��ig aussieht?
     * Versuche es mal mit dem Startwert "float tRedValueFloat = M_SQRT2;" und multipliziere ihn mit M_SQRT2.
     * Das gibt eine exponentielle Helligkeitszunahme (= das Verh�ltnis zwischen zwei benachbarten Werten ist immer gleich).
     */

    /*
     * Aufgabe 3. Gebe einen Regenbogen aus. Benutze die Funktion Wheel() um an die Regenbogenfarben zu kommen.
     * Wheel() akzeptiert Werte von 0 bis 255, erzeuge also 16 (NUMPIXELS) verschiedene Werte von 0 bis ungef�hr 255.
     */

//    for (unsigned int i = 0; i < NUM_PIXELS; i++) {
//        Serial.print("Wheel value=");
//        Serial.println(i * (256 / NUM_PIXELS));
//        MyNeoPixelBar.setPixelColor(i, Wheel(i * (256 / NUM_PIXELS)));
//    }
    delay(4000);

}

void loop() {

    static uint8_t tWheelOffset = 0; // "static" -> keep value between loops

    /*
     * Zusatzaufgabe 3. Der Regenbogen, der unten ausgegeben wird, soll pro Durchlauf bei einer anderen Farbe (Wert f�r Wheel()) anfangen.
     */

    for (unsigned int i = 0; i < NUM_PIXELS; i++) {
        Serial.print("Wheel value=");
        Serial.println(i * (256 / NUM_PIXELS));
        MyNeoPixelBar.setPixelColor(i, Wheel(i * (256 / NUM_PIXELS)));
    }
    MyNeoPixelBar.show();
    tWheelOffset++;

    delay(50);
}

/*
 * Rechne beispielhaft die Werte f�r 0 und 16 aus
 */
// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(uint8_t WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return Adafruit_NeoPixel::Color(255 - (WheelPos * 3), 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - (WheelPos * 3));
    } else {
        WheelPos -= 170;
        return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - (WheelPos * 3), 0);
    }
}

