/*
 * TB6612Motor.h
 *
 *  Created on: 12.05.2019
 *  Copyright (C) 2019-2020  Armin Joachimsmeyer
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

#ifndef TB6612DCMOTOR_H_
#define TB6612DCMOTOR_H_

#include <stdint.h>

#if ! defined(USE_FULL_BRIDGE_BREAKOUT_BOARD)
#  if ! defined(USE_STANDARD_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD)
/*
 * Saves 694 bytes program memory
 */
#define USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
#  endif
#include <Wire.h>

// Comment this out for building version for breakout board with TB6612FNG / Driver IC for Dual DC motor
//#define USE_FULL_BRIDGE_BREAKOUT_BOARD
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
// some PCA9685 specific constants
#define PCA9685_GENERAL_CALL_ADDRESS 0x00
#define PCA9685_SOFTWARE_RESET      6
#define PCA9685_DEFAULT_ADDRESS     0x40
#define PCA9685_MAX_CHANNELS        16 // 16 PWM channels on each PCA9685 expansion module
#define PCA9685_MODE1_REGISTER      0x0
#define PCA9685_MODE_1_RESTART        7
#define PCA9685_MODE_1_AUTOINCREMENT  5
#define PCA9685_MODE_1_SLEEP          4
#define PCA9685_FIRST_PWM_REGISTER  0x06
#define PCA9685_PRESCALE_REGISTER   0xFE

#define PCA9685_PRESCALER_FOR_1600_HZ ((25000000L /(4096L * 1600))-1) // = 3 at 1600 Hz

#  else
#include <Adafruit_MotorShield.h>
#  endif
#endif // ! defined(USE_FULL_BRIDGE_BREAKOUT_BOARD)

// Motor directions and stop modes. Are used for parameter aMotorDriverMode and sequence is determined by the Adafruit library API.
#define DIRECTION_FORWARD  0
#define DIRECTION_BACKWARD 1
#define oppositeDIRECTION(aDirection) (aDirection ^ DIRECTION_BACKWARD)
#define MOTOR_BRAKE 2
#define MOTOR_RELEASE 3
#define STOP_MODE_AND_MASK 0x03
#define STOP_MODE_OR_MASK 0x02
#define DEFAULT_STOP_MODE MOTOR_RELEASE
#define CheckStopMODE(aStopMode) ((aStopMode & STOP_MODE_AND_MASK) | STOP_MODE_OR_MASK)
#define CONVERSION_FOR_ADAFRUIT_API 1

struct EepromMotorInfoStruct {
    uint8_t MinSpeed;
    uint8_t StopSpeed;
    uint8_t MaxSpeed;
    uint8_t SpeedCompensation;
};
/*
 * Default values if EEPROM values are invalid
 */
#define DEFAULT_MIN_SPEED   45
#define DEFAULT_MAX_SPEED   80

/*
 * Motor control has 2 technical dimensions
 * 1. Motor driver control. Can be FORWARD, BACKWARD (BRAKE motor connection are shortened) or RELEASE ( motor connections are high impedance)
 * 2. Speed / PWM which is ignored for BRAKE or RELEASE
 */
class PWMDcMotor {
public:
    PWMDcMotor();

#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
    void init(uint8_t aForwardPin, uint8_t aBackwardPin, uint8_t aPWMPin);
#else
    void init(uint8_t aMotorNumber);
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
    /*
     * Own internal functions for communicating with the PCA9685 Expander IC on the Adafruit motor shield
     */
    void I2CWriteByte(uint8_t aAddress, uint8_t aData);
    void I2CSetPWM(uint8_t aPin, uint16_t aOn, uint16_t aOff);
    void I2CSetPin(uint8_t aPin, bool aSetToOn);
#  else
    Adafruit_DCMotor * Adafruit_MotorShield_DcMotor;
#  endif
#endif

    void setMotorDriverMode(uint8_t cmd);

    /*
     * Basic motor commands
     */
    void setSpeedCompensated(uint8_t aRequestedSpeed, uint8_t aRequestedDirection);
    void setSpeed(uint8_t aSpeedRequested, uint8_t aDirection);
    // not used yet
    void setSpeed(int aRequestedSpeed);
    void setSpeedCompensated(int aRequestedSpeed);

    void setStopMode(uint8_t aStopMode); // mode for Speed==0, MOTOR_BRAKE or MOTOR_RELEASE
    void stop(uint8_t aStopMode = DEFAULT_STOP_MODE); // sets CurrentSpeed (PWM) to 0 and driver mode to StopMode (MOTOR_BRAKE or MOTOR_RELEASE (default))

    void initGoDistanceCount(uint16_t aDistanceCount, uint8_t aRequestedDirection);
    // Not used yet
    void initGoDistanceCount(int16_t aDistanceCount);
    bool updateMotor();

    /*
     * EEPROM functions to read and store calibration and other control values (maxSpeed, SpeedCompensation)
     */
    void setEepromMotorValuesDefaults();
    void readMotorValuesFromEeprom();
    void writeMotorvaluesToEeprom();

#if defined(USE_FULL_BRIDGE_BREAKOUT_BOARD) || defined(USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD)
    uint8_t PWMPin;     // so set speed
    uint8_t ForwardPin; // if high, motor runs forward
    uint8_t BackwardPin;
#endif

    uint8_t MotorNumber; // number of this object starting with 0. Used for eeprom storage of parameters of more than one PWMDcMotor.
    /**********************************
     * Start of EEPROM values
     *********************************/
    /*
     * Minimum speed setting at which motor starts moving. Depend on current voltage, load and surface.
     * Is set by calibrate() and then stored (with the other values) in eeprom.
     */
    uint8_t MinSpeed;
    uint8_t MaxSpeed; // Maximum speed for go distance, set only from EEPROM value

    /*
     * Positive value to be subtracted from TargetSpeed to get CurrentSpeed to compensate for different left and right motors
     * Currently SpeedCompensation is in steps of 2 and only one motor can have a positive value, the other is set to zero.
     * Value is computed in synchronizeMotor()
     */
    uint8_t SpeedCompensation;
    /**********************************
     * End of EEPROM values
     *********************************/
    uint8_t CurrentSpeed;
    uint8_t CurrentDirection; // (of CurrentSpeed etc.) DIRECTION_FORWARD, DIRECTION_BACKWARD
    static bool MotorValuesHaveChanged;

    uint8_t StopMode; // used for speed == 0

    bool MotorMovesFixedDistance; // if true, stop if computedMillisOfMotorStopForDistance are reached
    uint32_t computedMillisOfMotorStopForDistance; // since we have no distance sensing, we must estimate a duration instead

};

#endif /* TB6612DCMOTOR_H_ */
