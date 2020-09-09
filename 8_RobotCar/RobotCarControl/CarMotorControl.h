/*
 * CarMotorControl.h
 *
 *  Motor control for a car with 2 encoder motors
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

#ifndef CARMOTORCONTROL_H_
#define CARMOTORCONTROL_H_

#include "EncoderMotor.h"
#include <stdint.h>

//#define USE_ENCODER_MOTOR_CONTROL

// turn directions
#define TURN_FORWARD DIRECTION_FORWARD
#define TURN_BACKWARD DIRECTION_BACKWARD
#define TURN_IN_PLACE 2

class CarMotorControl {
public:

    CarMotorControl();
//    virtual ~CarMotorControl();

#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
    void init(uint8_t aRightMotorForwardPin, uint8_t aRightMotorBackwardPin, uint8_t aRightPWMPin, uint8_t aLeftMotorForwardPin,
            uint8_t LeftMotorBackwardPin, uint8_t aLeftMotorPWMPin, uint8_t aPinFor2WDDetection);
#else
    void init(uint8_t aPinFor2WDDetection);
#endif
    void setDefaultsForFixedDistanceDriving();

    void calibrate();

    /*
     * Functions for moving a fixed distance
     */
    bool updateMotors();

    void initGoDistanceCentimeter(unsigned int aDistanceCentimeter, uint8_t aRequestedDirection); // only setup values
    void goDistanceCentimeter(unsigned int aDistanceCentimeter, uint8_t aRequestedDirection, void (*aLoopCallback)(void) = NULL); // Blocking function, uses waitUntilCarStopped
    // Not used yet
    void initGoDistanceCentimeter(int aDistanceCentimeter); // only setup values
    void goDistanceCentimeter(int aDistanceCentimeter, void (*aLoopCallback)(void) = NULL); // Blocking function, uses waitUntilCarStopped

    /*
     * Functions for rotation
     */
    void initRotateCar(int16_t aRotationDegrees, uint8_t aTurnDirection, bool aUseSlowSpeed = true);
    void rotateCar(int16_t aRotationDegrees, uint8_t aTurnDirection = TURN_IN_PLACE, bool aUseSlowSpeed = true,
            void (*aLoopCallback)(void) = NULL);

    /*
     * Start/Stop functions for infinite distance
     */
    void startCarAndWaitForFullSpeed(uint8_t aDriveDirection = DIRECTION_FORWARD);
    void stopCarAndWaitForIt(); // uses waitUntilCarStopped()

    void waitUntilCarStopped(void (*aLoopCallback)(void) = NULL);

    /*
     * Check motor state functions
     */
    bool isStopped();
    bool isState(uint8_t aState);
    bool needsFastUpdates();

    void resetControlValues();

    /*
     * Functions, which directly call motor functions for both motors
     */
    void setSpeedCompensated(uint8_t aRequestedSpeed, uint8_t aRequestedDirection);
    void stopMotors(uint8_t aStopMode = DEFAULT_STOP_MODE);
    // not used yet
    void setStopMode(uint8_t aStopMode);
    void setSpeed(int aRequestedSpeed);
    void setSpeedCompensated(int aRequestedSpeed);

    bool is2WDCar;
#if ! defined(USE_ENCODER_MOTOR_CONTROL)
    uint32_t computedMillisOfMotorStopForDistance; // since we have no distance sensing, we must estimate a duration instead
#endif
};

#ifdef USE_ENCODER_MOTOR_CONTROL
extern EncoderMotor rightMotor;
extern EncoderMotor leftMotor;
#else
extern PWMDcMotor rightMotor;
extern PWMDcMotor leftMotor;
#endif

#endif /* CARMOTORCONTROL_H_ */
