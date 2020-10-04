/*
 *  RobotCarFollower.cpp
 *
 *  Enables follower mode driving of a 2 or 4 wheel car with an Arduino.
 *  To find the target to follow, a HC-SR04 Ultrasonic sensor mounted on a SG90 Servo scans the area on demand. (not yet implemented)
 *
 *  Copyright (C) 2020  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of PWMMotorControl https://github.com/ArminJo/PWMMotorControl.
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

#include "CarMotorControl.h"
#include "Servo.h"
#include "HCSR04.h"

#define DISTANCE_MINIMUM_CENTIMETER 20 // If measured distance is less than this value, go backwards
#define DISTANCE_MAXIMUM_CENTIMETER 30 // If measured distance is greater than this value, go forward
#define DISTANCE_DELTA_CENTIMETER   (DISTANCE_MAXIMUM_CENTIMETER - DISTANCE_MINIMUM_CENTIMETER)

//#define VIN_2_LIPO

//#define PLOTTER_OUTPUT // Comment this out, if you want to see the result of the US distance sensor and resulting speed in Arduino plotter

#if defined(VIN_2_LIPO)
// values for 2xLIPO / 7.4 volt
#define START_SPEED                 30 // Speed PWM value at which car starts to move.
#define DRIVE_SPEED                 60 // Speed PWM value used for going fixed distance.
#define MAX_SPEED_FOLLOWER         100 // Max speed PWM value used for follower.
#else
// Values for 4xAA / 6.0 volt
#define START_SPEED                 80 // Speed PWM value at which car starts to move.
#define DRIVE_SPEED                150 // Speed PWM value used for going fixed distance.
#define MAX_SPEED_FOLLOWER         255 // Max speed PWM value used for follower.
#endif

#define SPEED_COMPENSATION_RIGHT     0 // If positive, this value is subtracted from the speed of the right motor, if negative, -value is subtracted from the left speed.

#if ! defined(USE_ADAFRUIT_MOTOR_SHIELD) // enable it in PWMDCMotor.h
/*
 * Pins for direct motor control with PWM and a dual full bridge e.g. TB6612 or L298.
 * Pins 9 + 10 are reserved for Servo
 * 2 + 3 are reserved for encoder input
 */
#define PIN_LEFT_MOTOR_FORWARD      4
#define PIN_LEFT_MOTOR_BACKWARD     7
#define PIN_LEFT_MOTOR_PWM          5 // Must be PWM capable

#define PIN_RIGHT_MOTOR_FORWARD     8
#define PIN_RIGHT_MOTOR_BACKWARD   12 // Pin 9 is already reserved for distance servo
#define PIN_RIGHT_MOTOR_PWM         6 // Must be PWM capable
#endif

#define PIN_DISTANCE_SERVO          9 // Servo Nr. 2 on Adafruit Motor Shield

#define PIN_SPEAKER                11

#define PIN_TRIGGER_OUT            A0 // Connections on the Arduino Sensor Shield
#define PIN_ECHO_IN                A1

//Car Control
CarMotorControl RobotCarMotorControl;
Servo DistanceServo;

unsigned int getDistanceAndPlayTone();

/*
 * Start of robot car control program
 */
void setup() {
    Serial.begin(115200);

    // Just to know which program is running on my Arduino
#ifdef PLOTTER_OUTPUT
    Serial.println(F("Distance[cm] Speed"));
#else
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_PWMMOTORCONTROL));
#endif

#ifdef USE_ADAFRUIT_MOTOR_SHIELD
    RobotCarMotorControl.init();
#else
    RobotCarMotorControl.init(PIN_RIGHT_MOTOR_FORWARD, PIN_RIGHT_MOTOR_BACKWARD, PIN_RIGHT_MOTOR_PWM, PIN_LEFT_MOTOR_FORWARD,
    PIN_LEFT_MOTOR_BACKWARD, PIN_LEFT_MOTOR_PWM);
#endif
    RobotCarMotorControl.setValuesForFixedDistanceDriving(START_SPEED, DRIVE_SPEED, SPEED_COMPENSATION_RIGHT);

    DistanceServo.attach(PIN_DISTANCE_SERVO);
    DistanceServo.write(90);
    initUSDistancePins(PIN_TRIGGER_OUT, PIN_ECHO_IN);

    tone(PIN_SPEAKER, 2200, 100);
    delay(200);
    tone(PIN_SPEAKER, 2200, 100);

    /*
     * Do not start immediately with driving
     */
    delay(5000);

    /*
     * Tone feedback for start of driving
     */
    tone(PIN_SPEAKER, 2200, 100);
    delay(200);
    tone(PIN_SPEAKER, 2200, 100);
}

void loop() {

    unsigned int tCentimeter = getDistanceAndPlayTone();
    unsigned int tSpeed;
    /*
     * TODO check if distance too high, then search for target in a different direction
     */

    if (tCentimeter > DISTANCE_MAXIMUM_CENTIMETER) {
        /*
         * Target too far -> drive forward with speed proportional to the gap
         */
        tSpeed = START_SPEED + (tCentimeter - DISTANCE_MAXIMUM_CENTIMETER) * 2;
        if (tSpeed > MAX_SPEED_FOLLOWER) {
            tSpeed = MAX_SPEED_FOLLOWER;
        }
#ifdef PLOTTER_OUTPUT
        Serial.print(tSpeed);
#else
        if (RobotCarMotorControl.getCarDirectionOrBrakeMode() != DIRECTION_FORWARD) {
            Serial.println(F("Go forward"));
        }
        Serial.print(F("Speed="));
        Serial.print(tSpeed);
#endif
#ifdef USE_ENCODER_MOTOR_CONTROL
        RobotCarMotorControl.startGoDistanceCentimeter(tSpeed, (tCentimeter - DISTANCE_MAXIMUM_CENTIMETER) + DISTANCE_DELTA_CENTIMETER / 2,
                DIRECTION_FORWARD);
#else
        RobotCarMotorControl.setSpeedCompensated(tSpeed, DIRECTION_FORWARD);
#endif

    } else if (tCentimeter < DISTANCE_MINIMUM_CENTIMETER) {
        /*
         * Target too close -> drive backwards
         */
        tSpeed = START_SPEED + (DISTANCE_MINIMUM_CENTIMETER - tCentimeter) * 4;
        if (tSpeed > MAX_SPEED_FOLLOWER) {
            tSpeed = MAX_SPEED_FOLLOWER;
        }
#ifdef PLOTTER_OUTPUT
        Serial.print(tSpeed);
#else
        if (RobotCarMotorControl.getCarDirectionOrBrakeMode() != DIRECTION_BACKWARD) {
            Serial.println(F("Go backward"));
        }
        Serial.print(F("Speed="));
        Serial.print(tSpeed);
#endif
#ifdef USE_ENCODER_MOTOR_CONTROL
        RobotCarMotorControl.startGoDistanceCentimeter(tSpeed, (DISTANCE_MINIMUM_CENTIMETER - tCentimeter) + DISTANCE_DELTA_CENTIMETER / 2,
                DIRECTION_BACKWARD);
#else
        RobotCarMotorControl.setSpeedCompensated(tSpeed, DIRECTION_BACKWARD);
#endif
    } else {
        /*
         * Target is in the right distance -> stop once
         */
        if (RobotCarMotorControl.getCarDirectionOrBrakeMode() != MOTOR_RELEASE) {
#ifndef PLOTTER_OUTPUT
            Serial.print(F("Stop"));
#endif
            RobotCarMotorControl.stopMotors(MOTOR_RELEASE);
        }
    }

    Serial.println();
#ifdef USE_ENCODER_MOTOR_CONTROL
    RobotCarMotorControl.delayAndUpdateMotors(1000);
#else
    delay(100);
#endif
}

unsigned int getDistanceAndPlayTone() {
    /*
     * Get distance
     */
    unsigned int tCentimeter = getUSDistanceAsCentiMeter();
#ifdef PLOTTER_OUTPUT
    Serial.print(tCentimeter);
    Serial.print(' ');
#else
    Serial.print("Distance=");
    Serial.print(tCentimeter);
    Serial.print("cm. ");
#endif
    /*
     * Play tone
     */
    int tFrequency = map(tCentimeter, 0, 100, 110, 1760); // 4 octaves per meter
    tone(PIN_SPEAKER, tFrequency);
    return tCentimeter;
}
