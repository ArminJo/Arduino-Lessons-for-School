/*
 *  RobotCar_Follower.cpp
 *
 *  Enables follower mode driving of a 2 or 4 wheel car with an Arduino and a Adafruit Motor Shield V2.
 *  To find the target to follow, a HC-SR04 Ultrasonic sensor mounted on a SG90 Servo scans the area on demand.
 *
 *  Copyright (C) 2016  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

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
CarMotorControl RobotCarMotorControl;
//#define PLOTTER_OUTPUT

unsigned int getDistanceAndPlayTone();

/*
 * Start of robot car control program
 */
void setup() {
    Serial.begin(115200);

    // Just to know which program is running on my Arduino
#ifdef PLOTTER_OUTPUT
    Serial.println(F("Distance[cm]"));
#else
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));
#endif

    RobotCarMotorControl.init(PIN_TWO_WD_DETECTION);
    RobotCarMotorControl.setDefaultsForFixedDistanceDriving();
    initDistance();

    tone(PIN_SPEAKER, 2200, 100);
    delay(200);
    tone(PIN_SPEAKER, 2200, 100);
    delay(500);
    RobotCarMotorControl.setSpeed(60);
}

bool sFoundPerson = false;
void loop() {

    unsigned int tCentimeter = getDistanceAndPlayTone();

    if (tCentimeter > 30) {
        /*
         * TODO check if distance too high, then search person in another direction
         */
        Serial.println(F("Go forward"));
        RobotCarMotorControl.startCarAndWaitForFullSpeed();
    } else if (tCentimeter < 22) {
        Serial.println(F("Go backward"));
        RobotCarMotorControl.startCarAndWaitForFullSpeed(DIRECTION_BACKWARD);
    } else {
        sFoundPerson = true;
        Serial.println(F("Stop"));
        RobotCarMotorControl.stopMotors(false);
    }
    delay(40); // the IR sensor takes 39 ms for one measurement
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
    Serial.print("cm. ");
#endif
    /*
     * play tone
     */
    int tFrequency = map(tCentimeter, 0, 100, 110, 1760); // 4 octaves per meter
    tone(PIN_SPEAKER, tFrequency);
    return tCentimeter;
}
