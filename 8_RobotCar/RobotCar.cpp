/*
 *  RobotCar.cpp
 *
 *  Variant without BlueDisplay control.
 *
 *  Enables autonomous driving of a 2 or 4 wheel car with an Arduino and a Adafruit Motor Shield V2.
 *  To avoid obstacles a HC-SR04 Ultrasonic sensor mounted on a SG90 Servo continuously scans the area.
 *
 *  Copyright (C) 2016-2020  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-RobotCar https://github.com/ArminJo/Arduino-RobotCar.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#include <Arduino.h>

#include "RobotCar.h"
#include "Distance.h"

#include "HCSR04.h"

#define VERSION_EXAMPLE "1.0"

//Car Control
CarMotorControl RobotCar;

//#define PLOTTER_OUTPUT

unsigned int getDistanceAndPlayTone();

/*
 * Start of robot car control program
 */
void setup() {
    Serial.begin(115200);
    Serial.print(F("MCUSR="));
    Serial.println(MCUSR, HEX);

    // Just to know which program is running on my Arduino
#ifdef PLOTTER_OUTPUT
    Serial.println("Distance[cm]");
#else
    Serial.println("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__);
#endif

    RobotCar.init(PIN_TWO_WD_DETECTION);
    RobotCar.setDefaultsForFixedDistanceDriving();
    initDistance();

    tone(PIN_SPEAKER, 2200, 100);
    delay(500);
    RobotCar.setSpeed(60);
}

void loop() {

    unsigned int tCentimeter = getDistanceAndPlayTone();

    if (tCentimeter > 40) {
        Serial.println("Go distance 10 cm");
        RobotCar.goDistanceCentimeter(10);
    } else if (tCentimeter < 20) {
        Serial.println("Go distance -10 cm");
        RobotCar.goDistanceCentimeter(-10);
    } else {
        delay(50);
    }
}

unsigned int getDistanceAndPlayTone() {
    /*
     * Get distance
     */
    unsigned int tCentimeter = getUSDistanceAsCentiMeter();
#ifdef PLOTTER_OUTPUT
    Serial.println(tCentimeter);
#else
    Serial.print("Distance=");
    Serial.print(tCentimeter);
    Serial.println("cm.");
#endif
    /*
     * play tone
     */
    int tFrequency = map(tCentimeter, 0, 100, 440, 1760); // 2 octaves per meter
    tone(PIN_SPEAKER, tFrequency, 200);
    return tCentimeter;
}

