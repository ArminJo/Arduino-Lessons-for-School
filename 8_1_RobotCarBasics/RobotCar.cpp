/*
 *  RobotCar.cpp
 *
 *  Template for your RobotCar control.
 *  Like https://github.com/ArminJo/PWMMotorControl/blob/master/examples/RobotCarBasic/RobotCarBasic.ino
 *
 *  Copyright 2019-2022 Armin Joachimsmeyer
 *  This code is released under GPLv3 license.
 *
 *  This file is part of Arduino-Lessons-for-School https://github.com/ArminJo/Arduino-Lessons-for-School.
 *
 *  Arduino-Lessons-for-School is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/gpl.html>.
 */

#include <Arduino.h>

/*
 * Car configuration
 * For a complete list of available configurations see RobotCarConfigurations.h
 * https://github.com/ArminJo/Arduino-RobotCar/blob/master/src/RobotCarConfigurations.h
 */
//#define TBB6612_4WD_4AA_BASIC_CONFIGURATION       // China set with TB6612 mosfet bridge + 4AA.
//#define TBB6612_4WD_4AA_VIN_CONFIGURATION         // China set with TB6612 mosfet bridge + 4AA + VIN voltage divider.
//#define TBB6612_4WD_4AA_FULL_CONFIGURATION        // China set with TB6612 mosfet bridge + 4AA + VIN voltage divider + MPU6050.
//#define TBB6612_4WD_2LI_ION_BASIC_CONFIGURATION   // China set with TB6612 mosfet bridge + 2 Li-ion.
//#define TBB6612_4WD_2LI_ION_FULL_CONFIGURATION    // China set with TB6612 mosfet bridge + 2 Li-ion + VIN voltage divider + MPU6050.
//#define L298_2WD_4AA_BASIC_CONFIGURATION          // Default. Basic = Lafvin 2WD model using L298 bridge. Uno board with series diode for VIN + 4 AA batteries.
//#define L298_4WD_4AA_BASIC_CONFIGURATION          // China set with L298 + 4AA.
//#define L298_2WD_2LI_ION_BASIC_CONFIGURATION      // Basic = Lafvin 2WD model using L298 bridge. Uno board with series diode for VIN + 2 Li-ion.
//#define L298_2WD_VIN_IR_DISTANCE_CONFIGURATION    // L298_2WD_2LI_ION_BASIC + VIN voltage divider + IR distance
//#define L298_2WD_VIN_IR_IMU_CONFIGURATION         // L298_2WD_2LI_ION_BASIC + VIN voltage divider + IR distance + MPU6050
//#define MECANUM_DISTANCE_CONFIGURATION            // Nano Breadboard version with Arduino NANO, TB6612 mosfet bridge and 4 mecanum wheels + US distance + servo

#define USE_STANDARD_SERVO_LIBRARY
#include "RobotCarConfigurations.h" // sets e.g. USE_ENCODER_MOTOR_CONTROL, USE_ADAFRUIT_MOTOR_SHIELD
#include "RobotCarPinDefinitionsAndMore.h"

#include "Servo.h"
#include "Distance.hpp"
#include "HCSR04.h"
#include "CarPWMMotorControl.hpp"
#include "RobotCarUtils.hpp"

#define rightMotor RobotCar.rightCarMotor
#define leftMotor   RobotCar.leftCarMotor
/*
 * Start of robot car control program
 */
void setup() {
    Serial.begin(115200);
    Serial.println("START " __FILE__ " from " __DATE__); // Just to know which program is running on my Arduino

    initRobotCarPWMMotorControl();

    /*
     * Initialize pins for the servo and the HC-SR04 ultrasonic distance measurement
     */
    initDistance();

    /*
     * Set US servo to forward position
     */
    DistanceServo.write(90);

    /*
     * Move it as signal, that we are booted
     */
    delay(500);
    DistanceServo.write(135);
    delay(500);
    DistanceServo.write(45);
    delay(500);
    DistanceServo.write(90);

    tone(PIN_BUZZER, 2200, 200);
    delay(2000);

    /*
     * Rotate both motors forward, wait a second and then stop
     * Speed can go from 0 to 255 (MAX_SPEED_PWM)
     * DEFAULT_DRIVE_SPEED_PWM corresponds to 2 volt motor supply
     */
    leftMotor.setSpeedPWMAndDirection(120, DIRECTION_FORWARD);
    rightMotor.setSpeedPWMAndDirection(120, DIRECTION_FORWARD);
    delay(500); // do not go too far
    leftMotor.stop();
    rightMotor.stop();

    // wait 10 seconds before entering the loop
    delay(10000);

}

void loop() {

    /*
     * Measure distance with the HC-SR04 ultrasonic distance device and print it
     */
    unsigned int tCentimeter = getUSDistanceAsCentimeter(); // Timeout returns 0
//    unsigned int tCentimeter = getIRDistanceAsCentimeter();
    Serial.print("Distance=");
    Serial.print(tCentimeter);
    Serial.println(" cm");

    if (tCentimeter > 0 && tCentimeter < 5) {
        RobotCar.setSpeedPWMAndDirection(DEFAULT_DRIVE_SPEED_PWM, DIRECTION_BACKWARD);
    } else {
        RobotCar.stop();
    }

    /*
     * 1. Keep distance: If distance too high, drive forward, if distance too low drive backwards.
     * 2. Drive until distance too low, then stop, go back, turn random amount and measure and drive/turn again.
     */
    delay(500);
}
