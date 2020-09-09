/*
 * CarMotorControl.cpp
 *
 *  Contains functions for control of the 2 motors of a car like setDirection, goDistanceCentimeter() and rotateCar().
 *  Checks input of PIN aPinFor2WDDetection since we need different factors for rotating a 4 wheel and a 2 wheel car.
 *
 *  Requires EncoderMotor.cpp
 *
 *  Created on: 16.09.2016
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
 */

#include <Arduino.h>
#include "CarMotorControl.h"
#include "EncoderMotor.h"

#ifdef USE_ENCODER_MOTOR_CONTROL
EncoderMotor rightMotor;
EncoderMotor leftMotor;
#else
PWMDcMotor rightMotor;
PWMDcMotor leftMotor;
#endif

CarMotorControl::CarMotorControl() { // @suppress("Class members should be properly initialized")
}

#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
void CarMotorControl::init(uint8_t aRightMotorForwardPin, uint8_t aRightMotorBackwardPin, uint8_t aRightPWMPin,
        uint8_t aLeftMotorForwardPin, uint8_t LeftMotorBackwardPin, uint8_t aLeftMotorPWMPin, uint8_t aPinFor2WDDetection) {
    pinMode(aPinFor2WDDetection, INPUT_PULLUP);

    leftMotor.init(aLeftMotorForwardPin, LeftMotorBackwardPin, aLeftMotorPWMPin);
    rightMotor.init(aRightMotorForwardPin, aRightMotorBackwardPin, aRightPWMPin);
    /*
     * For slot type optocoupler interrupts on pin PD2 + PD3
     */
    EncoderMotor::enableINT0AndINT1Interrupts();

    is2WDCar = !digitalRead(aPinFor2WDDetection);
}
#else
void CarMotorControl::init(uint8_t aPinFor2WDDetection) {
    pinMode(aPinFor2WDDetection, INPUT_PULLUP);

    leftMotor.init(0);
    rightMotor.init(1);
#ifdef USE_ENCODER_MOTOR_CONTROL
    /*
     * For slot type optocoupler interrupts on pin PD2 + PD3
     */
    EncoderMotor::enableINT0AndINT1Interrupts();
#endif

    is2WDCar = !digitalRead(aPinFor2WDDetection);
}
#endif

/*
 * Sets default values for min and max speed and reset compensation
 */
void CarMotorControl::setDefaultsForFixedDistanceDriving() {
    rightMotor.setEepromMotorValuesDefaults();
    leftMotor.setEepromMotorValuesDefaults();
}

/*
 *  Direct motor control, no state or flag handling
 *  Not used yet
 */
void CarMotorControl::setSpeed(int aRequestedSpeed) {
    rightMotor.setSpeed(aRequestedSpeed);
    leftMotor.setSpeed(aRequestedSpeed);
}

/*
 * Sets signed speed adjusted by current compensation value and handle motor state and flags
 * Not used yet
 */
void CarMotorControl::setSpeedCompensated(int aRequestedSpeed) {
    rightMotor.setSpeedCompensated(aRequestedSpeed);
    leftMotor.setSpeedCompensated(aRequestedSpeed);
}

/*
 * Sets speed adjusted by current compensation value and handle motor state and flags
 */
void CarMotorControl::setSpeedCompensated(uint8_t aRequestedSpeed, uint8_t aRequestedDirection) {
    rightMotor.setSpeedCompensated(aRequestedSpeed, aRequestedDirection);
    leftMotor.setSpeedCompensated(aRequestedSpeed, aRequestedDirection);
}

/*
 * Stop car
 * @param aStopMode can be: MOTOR_BRAKE or MOTOR_RELEASE (default)
 */
void CarMotorControl::stopMotors(uint8_t aStopMode) {
    rightMotor.stop(aStopMode);
    leftMotor.stop(aStopMode);
}

/*
 * Not used yet
 * @param aStopMode can be: MOTOR_BRAKE or MOTOR_RELEASE (default)
 */
void CarMotorControl::setStopMode(uint8_t aStopMode) {
    rightMotor.setStopMode(aStopMode);
    leftMotor.setStopMode(aStopMode);
}

/*
 * Stop car and reset all control values as speed, distances, debug values to 0x00
 * Leave calibration and compensation (EEPROM) values unaffected.
 */
void CarMotorControl::resetControlValues() {
#ifdef USE_ENCODER_MOTOR_CONTROL
    rightMotor.resetControlValues();
    leftMotor.resetControlValues();
#endif
}

/*
 * If motor is accelerating or decelerating then updateMotor needs to be called at a fast rate otherwise it will not work correctly
 * Used to suppress time consuming display of motor values
 */
bool CarMotorControl::needsFastUpdates() {
#ifdef USE_ENCODER_MOTOR_CONTROL
    return (rightMotor.State == MOTOR_STATE_RAMP_DOWN || rightMotor.State == MOTOR_STATE_RAMP_UP
            || leftMotor.State == MOTOR_STATE_RAMP_DOWN || leftMotor.State == MOTOR_STATE_RAMP_UP);
#else
    return false;
#endif
}

/*
 * @return true if not stopped (motor expects another update)
 */
bool CarMotorControl::updateMotors() {
    bool tMotorsNotStopped = rightMotor.updateMotor();
    tMotorsNotStopped |= leftMotor.updateMotor();
    return tMotorsNotStopped;
}

/*
 * initialize motorInfo fields DirectionForward, CurrentMaxSpeed, DistanceTickCounter and optional NextChangeMaxTargetCount.
 */
void CarMotorControl::initGoDistanceCentimeter(unsigned int aDistanceCentimeter, uint8_t aRequestedDirection) {
    rightMotor.initGoDistanceCount(aDistanceCentimeter * FACTOR_CENTIMETER_TO_COUNT, aRequestedDirection);
    leftMotor.initGoDistanceCount(aDistanceCentimeter * FACTOR_CENTIMETER_TO_COUNT, aRequestedDirection);
}

void CarMotorControl::goDistanceCentimeter(unsigned int aDistanceCentimeter, uint8_t aRequestedDirection,
        void (*aLoopCallback)(void)) {
    initGoDistanceCentimeter(aDistanceCentimeter, aRequestedDirection);
    waitUntilCarStopped(aLoopCallback);
}

/*
 * initialize motorInfo fields DirectionForward, CurrentMaxSpeed, DistanceTickCounter and optional NextChangeMaxTargetCount.
 * Not used yet
 */
void CarMotorControl::initGoDistanceCentimeter(int aDistanceCentimeter) {
    rightMotor.initGoDistanceCount(aDistanceCentimeter * FACTOR_CENTIMETER_TO_COUNT);
    leftMotor.initGoDistanceCount(aDistanceCentimeter * FACTOR_CENTIMETER_TO_COUNT);
}
/**
 * Wait until distance is reached
 * @param  aLoopCallback called until car has stopped to avoid blocking
 * Not used yet
 */
void CarMotorControl::goDistanceCentimeter(int aDistanceCentimeter, void (*aLoopCallback)(void)) {
    initGoDistanceCentimeter(aDistanceCentimeter);
    waitUntilCarStopped(aLoopCallback);
}

/*
 * Start motor for "infinite" distance and then blocking wait until both motors are at full speed
 * If motor is still running, just update motor.
 */
void CarMotorControl::startCarAndWaitForFullSpeed(uint8_t aDriveDirection) {
#ifdef USE_ENCODER_MOTOR_CONTROL
    if (rightMotor.State == MOTOR_STATE_STOPPED || leftMotor.State == MOTOR_STATE_STOPPED
            || rightMotor.CurrentDirection != aDriveDirection) {
        /*
         * Start only if not already started or direction changed
         */
        initGoDistanceCentimeter(INFINITE_DISTANCE_CM, aDriveDirection);

#ifdef DEBUG
        Serial.print(F("Start car dir="));
        Serial.println(aDriveDirection);
#endif
    }
    /*
     * blocking wait for start
     */
    bool tMotorsNotStopped;
    do {
        tMotorsNotStopped = rightMotor.updateMotor();
        tMotorsNotStopped |= leftMotor.updateMotor();
    } while (tMotorsNotStopped && (rightMotor.State != MOTOR_STATE_FULL_SPEED || leftMotor.State != MOTOR_STATE_FULL_SPEED));
#else
    rightMotor.setSpeedCompensated(rightMotor.MaxSpeed, aDriveDirection);
    leftMotor.setSpeedCompensated(leftMotor.MaxSpeed, aDriveDirection);
#endif
}

/*
 * Stop car with ramp and give DistanceCountAfterRampUp counts for braking.
 *
 * Set NextChangeMaxTargetCount to change state from MOTOR_STATE_FULL_SPEED to MOTOR_STATE_RAMP_DOWN
 * Use DistanceCountAfterRampUp as ramp down count
 * Blocking wait for stop
 */
void CarMotorControl::stopCarAndWaitForIt() {
    if (isStopped()) {
        return;
    }
#ifdef USE_ENCODER_MOTOR_CONTROL
    rightMotor.NextChangeMaxTargetCount = rightMotor.EncoderCount;
    rightMotor.TargetDistanceCount = rightMotor.EncoderCount + rightMotor.DistanceCountAfterRampUp;
    leftMotor.NextChangeMaxTargetCount = leftMotor.EncoderCount;
    leftMotor.TargetDistanceCount = leftMotor.EncoderCount + leftMotor.DistanceCountAfterRampUp;
#endif
    /*
     * blocking wait for stop
     */
    waitUntilCarStopped();
}

/*
 * Wait with optional wait loop callback
 */
void CarMotorControl::waitUntilCarStopped(void (*aLoopCallback)(void)) {
    do {
        rightMotor.updateMotor();
        leftMotor.updateMotor();
        if (aLoopCallback != NULL) {
            aLoopCallback();
        }
    } while (!isStopped());
}

bool CarMotorControl::isState(uint8_t aState) {
#ifdef USE_ENCODER_MOTOR_CONTROL
    return (rightMotor.State == aState && leftMotor.State == aState);
#else
    return false;
#endif
}

bool CarMotorControl::isStopped() {
    return (rightMotor.CurrentSpeed == 0 && leftMotor.CurrentSpeed == 0);
}

/**
 * Set distances and speed for 2 motors to turn the requested angle
 * @param  aRotationDegrees positive -> turn left, negative -> turn right
 * @param  aTurnDirection direction of turn TURN_FORWARD, TURN_BACKWARD or TURN_IN_PLACE
 * @param  if aUseSlowSpeed is true then use slower speed (1.5 times MinSpeed) for rotation to be more exact
 */
void CarMotorControl::initRotateCar(int16_t aRotationDegrees, uint8_t aTurnDirection, bool aUseSlowSpeed) {
    int tDistanceCountRight;
    int tDistanceCountLeft;
    int tDistanceCount;

    uint8_t tTurnDirectionRightMotor = aTurnDirection; // set turn direction as start direction
    uint8_t tTurnDirectionLeftMotor = aTurnDirection;
    if (aTurnDirection == TURN_BACKWARD) {
        // swap turn sign / (left / right) to enable other motor
        aRotationDegrees = -aRotationDegrees;
    }

    if (is2WDCar) {
        tDistanceCount = (aRotationDegrees * FACTOR_DEGREE_TO_COUNT_2WD_CAR) + 0.5;
    } else {
        tDistanceCount = (aRotationDegrees * FACTOR_DEGREE_TO_COUNT_4WD_CAR) + 0.5;
    }

    if (aRotationDegrees > 0) {
        // turn left, compute values for TURN_FORWARD
        tDistanceCountRight = tDistanceCount;
        tDistanceCountLeft = 0;
        if (aTurnDirection == TURN_IN_PLACE) {
            tDistanceCountRight /= 2;
            tDistanceCountLeft = tDistanceCountRight;
            tTurnDirectionLeftMotor = oppositeDIRECTION(tTurnDirectionLeftMotor);
        }
    } else {
        // turn right, compute values for TURN_FORWARD
        tDistanceCountLeft = tDistanceCount;
        tDistanceCountLeft = -tDistanceCountLeft;
        tDistanceCountRight = 0;
        if (aTurnDirection == TURN_IN_PLACE) {
            tDistanceCountLeft /= 2;
            tDistanceCountRight = tDistanceCountLeft;
            tTurnDirectionRightMotor = oppositeDIRECTION(tTurnDirectionRightMotor);
        }
    }

    // This in turn sets CurrentMaxSpeed to MaxSpeed.
    rightMotor.initGoDistanceCount(tDistanceCountRight, tTurnDirectionRightMotor);
    leftMotor.initGoDistanceCount(tDistanceCountLeft, tTurnDirectionLeftMotor);
    if (aUseSlowSpeed) {
        // adjust MaxSpeed
#ifdef USE_ENCODER_MOTOR_CONTROL
        rightMotor.CurrentMaxSpeed = rightMotor.MinSpeed + rightMotor.MinSpeed / 2;
        leftMotor.CurrentMaxSpeed = leftMotor.MinSpeed + leftMotor.MinSpeed / 2;
#else
        rightMotor.setSpeedCompensated(rightMotor.MinSpeed + rightMotor.MinSpeed / 2, rightMotor.CurrentDirection);
        leftMotor.setSpeedCompensated(leftMotor.MinSpeed + leftMotor.MinSpeed / 2, leftMotor.CurrentDirection);
#endif
    }
}

/*
 * @param  aRotationDegrees positive -> turn left, negative -> turn right
 * @param  aLoopCallback avoid blocking and call aLoopCallback on waiting for stop
 */
void CarMotorControl::rotateCar(int16_t aRotationDegrees, uint8_t aTurnDirection, bool aUseSlowSpeed, void (*aLoopCallback)(void)) {
    if (aRotationDegrees != 0) {
        initRotateCar(aRotationDegrees, aTurnDirection, aUseSlowSpeed);
        waitUntilCarStopped(aLoopCallback);
    }
}

/*
 * generates a rising ramp and detects the first movement -> this sets dead band / minimum Speed
 */
void CarMotorControl::calibrate() {
    stopMotors();
    resetControlValues();
#ifdef USE_ENCODER_MOTOR_CONTROL

    rightMotor.MinSpeed = 0;
    leftMotor.MinSpeed = 0;

    /*
     * increase motor speed by 1 until motor moves
     */
    for (uint8_t tSpeed = 20; tSpeed != 0xFF; ++tSpeed) {
        if (rightMotor.MinSpeed == 0) {
            rightMotor.setSpeed(tSpeed, DIRECTION_FORWARD);
            rightMotor.CurrentSpeed = tSpeed;
        }
        if (leftMotor.MinSpeed == 0) {
            leftMotor.setSpeed(tSpeed, DIRECTION_FORWARD);
            leftMotor.CurrentSpeed = tSpeed;
        }

        delay(100);
        /*
         * Check if wheel moved
         */
        uint8_t tMotorMovingCount = 0;
        /*
         * Store speed after 6 counts (3cm)
         */
        if (rightMotor.MinSpeed == 0 && rightMotor.EncoderCount > 6) {
            rightMotor.MinSpeed = tSpeed;
            tMotorMovingCount++;
        }
        if (leftMotor.MinSpeed == 0 && leftMotor.EncoderCount > 6) {
            leftMotor.MinSpeed = tSpeed;
            tMotorMovingCount++;
        }
        if (tMotorMovingCount >= 2) {
            // Do not end loop if one motor still not moving
            break;
        }
    }

    /*
     * TODO calibrate StopSpeed separately
     */

    rightMotor.writeMotorvaluesToEeprom();
    leftMotor.writeMotorvaluesToEeprom();

    stopMotors();
#endif
}

#ifdef USE_ENCODER_MOTOR_CONTROL
// ISR for PIN PD2 / RIGHT
ISR(INT0_vect) {
    rightMotor.handleEncoderInterrupt();
}

// ISR for PIN PD3 / LEFT
ISR(INT1_vect) {
    leftMotor.handleEncoderInterrupt();
}
#endif
