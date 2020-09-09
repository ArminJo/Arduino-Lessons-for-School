/*
 * TB6612Motor.cpp
 *
 * Low level motor control for Adafruit_MotorShield OR breakout board with TB6612FNG / Driver IC for dual DC motor
 *
 * Motor control has 2 parameters:
 * 1. Speed / PWM which is ignored for BRAKE or RELEASE. This library also accepts signed speed (including the direction as sign).
 * 2. Direction / MotorDriverMode. Can be FORWARD, BACKWARD (BRAKE motor connection are shortened) or RELEASE ( motor connections are high impedance)
 *
 *  Created on: 12.05.2019
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

#include <PWMDcMotor.h>

bool PWMDcMotor::MotorValuesHaveChanged; // for printing

PWMDcMotor::PWMDcMotor() { // @suppress("Class members should be properly initialized")
    StopMode = DEFAULT_STOP_MODE;
}

#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
void PWMDcMotor::init(uint8_t aForwardPin, uint8_t aBackwardPin, uint8_t aPWMPin) {
    ForwardPin = aForwardPin;
    BackwardPin = aBackwardPin;
    PWMPin = aPWMPin;
    StopMode = MOTOR_RELEASE;

    pinMode(aForwardPin, OUTPUT);
    pinMode(aBackwardPin, OUTPUT);
    pinMode(aPWMPin, OUTPUT);

    readMotorValuesFromEeprom();
    stop();
}

#else
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
void PWMDcMotor::I2CWriteByte(uint8_t aAddress, uint8_t aData) {
    Wire.beginTransmission(0x60);
    Wire.write(aAddress);
    Wire.write(aData);
    Wire.endTransmission();
}

void PWMDcMotor::I2CSetPWM(uint8_t aPin, uint16_t aOn, uint16_t aOff) {
    Wire.beginTransmission(0x60);
    Wire.write((PCA9685_FIRST_PWM_REGISTER) + 4 * aPin);
    Wire.write(aOn);
    Wire.write(aOn >> 8);
    Wire.write(aOff);
    Wire.write(aOff >> 8);
    Wire.endTransmission();
}

void PWMDcMotor::I2CSetPin(uint8_t aPin, bool aSetToOn) {
    if (aSetToOn) {
        I2CSetPWM(aPin, 4096, 0);
    } else {
        I2CSetPWM(aPin, 0, 0);
    }
}

#  else
// Create the motor shield object with the default I2C address
Adafruit_MotorShield sAdafruitMotorShield = Adafruit_MotorShield();
#  endif // USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD

/*
 * aMotorNumber from 0 to 1
 * Currently motors 2 and 3 are not required/supported
 */
void PWMDcMotor::init(uint8_t aMotorNumber) {
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
    if (aMotorNumber == 0) {
        PWMPin = 8;
        BackwardPin = 9;
        ForwardPin = 10;
    } else {
        PWMPin = 13;
        BackwardPin = 12;
        ForwardPin = 11;
    }

    Wire.begin();
#if defined (ARDUINO_ARCH_AVR) // Other platforms do not have this new function
    Wire.setWireTimeout(5000); // Sets timeout to 5 ms. default is 25 ms.
#endif
    // Reset PCA9685
    Wire.beginTransmission(PCA9685_GENERAL_CALL_ADDRESS);
    Wire.write(PCA9685_SOFTWARE_RESET);
    Wire.endTransmission();
    // Set expander to 1600 HZ
    I2CWriteByte(PCA9685_MODE1_REGISTER, _BV(PCA9685_MODE_1_SLEEP)); // go to sleep
    I2CWriteByte(PCA9685_PRESCALE_REGISTER, PCA9685_PRESCALER_FOR_1600_HZ); // set the prescaler
    delay(2); // > 500 us before the restart bit according to datasheet
    I2CWriteByte(PCA9685_MODE1_REGISTER, _BV(PCA9685_MODE_1_RESTART) | _BV(PCA9685_MODE_1_AUTOINCREMENT)); // reset sleep and enable auto increment

#  else
    Adafruit_MotorShield_DcMotor = sAdafruitMotorShield.getMotor(aMotorNumber + 1);
    sAdafruitMotorShield.begin();
#  endif

    readMotorValuesFromEeprom();
    stop();
}
#endif // USE_FULL_BRIDGE_BREAKOUT_BOARD

/*
 *  @brief  Control the DC motor driver direction and stop mode
 *  @param  aMotorDriverMode The mode can be FORWARD, BACKWARD (BRAKE motor connection are shortened) or RELEASE ( motor connections are high impedance)
 */
void PWMDcMotor::setMotorDriverMode(uint8_t aMotorDriverMode) {
#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
    switch (aMotorDriverMode) {
    case DIRECTION_FORWARD:
        digitalWrite(BackwardPin, LOW); // take low first to avoid 'break'
        digitalWrite(ForwardPin, HIGH);
        break;
    case DIRECTION_BACKWARD:
        digitalWrite(ForwardPin, LOW); // take low first to avoid 'break'
        digitalWrite(BackwardPin, HIGH);
        break;
    case MOTOR_BRAKE:
        digitalWrite(ForwardPin, HIGH);
        digitalWrite(BackwardPin, HIGH);
        break;
    case MOTOR_RELEASE:
        digitalWrite(ForwardPin, LOW);
        digitalWrite(BackwardPin, LOW);
        break;
    }
#else
    // until here DIRECTION_FORWARD is 0 back is 1, Adafruit library starts with 1
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
    switch (aMotorDriverMode) {
    case DIRECTION_FORWARD:
        I2CSetPin(BackwardPin, LOW); // take low first to avoid 'break'
        I2CSetPin(ForwardPin, HIGH);
        break;
    case DIRECTION_BACKWARD:
        I2CSetPin(ForwardPin, LOW); // take low first to avoid 'break'
        I2CSetPin(BackwardPin, HIGH);
        break;
    case MOTOR_BRAKE:
        I2CSetPin(ForwardPin, HIGH);
        I2CSetPin(BackwardPin, HIGH);
        break;
    case MOTOR_RELEASE:
        I2CSetPin(ForwardPin, LOW);
        I2CSetPin(BackwardPin, LOW);
        break;
    }
#  else
    Adafruit_MotorShield_DcMotor->run(aMotorDriverMode + CONVERSION_FOR_ADAFRUIT_API);
#  endif
#endif

}

/*
 *  @brief  Control the DC Motor speed/throttle
 *  @param  speed The 8-bit PWM value, 0 is off, 255 is on forward -255 is on backward
 *  First set driver mode, then set PWM
 */
void PWMDcMotor::setSpeed(uint8_t aSpeedRequested, uint8_t aDirection) {
    CurrentSpeed = aSpeedRequested;
    MotorValuesHaveChanged = true;

    if (aSpeedRequested == 0) {
        setMotorDriverMode(StopMode);
    } else {
        setMotorDriverMode(aDirection);
    }
#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
    analogWrite(PWMPin, aSpeedRequested);
#else
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
    I2CSetPWM(PWMPin, 0, 16 * aSpeedRequested);
#  else
    Adafruit_MotorShield_DcMotor->setSpeed(aSpeedRequested);
#  endif
#endif
}

/*
 * Subtracts SpeedCompensation from aRequestedSpeed before applying
 */
void PWMDcMotor::setSpeedCompensated(uint8_t aRequestedSpeed, uint8_t aRequestedDirection) {
    if (aRequestedSpeed == 0) {
        stop(StopMode);
    } else {
        CurrentDirection = aRequestedDirection;
// avoid underflow
        if (aRequestedSpeed > SpeedCompensation) {
            CurrentSpeed = aRequestedSpeed - SpeedCompensation;
        } else {
            CurrentSpeed = 0;
        }
        PWMDcMotor::setSpeed(CurrentSpeed, CurrentDirection); // output PWM value to motor
    }
}

/*
 * Not used yet
 */
void PWMDcMotor::setSpeed(int aSpeedRequested) {
    if (aSpeedRequested < 0) {
        aSpeedRequested = -aSpeedRequested;
        setSpeed(aSpeedRequested, DIRECTION_BACKWARD);
    } else {
        setSpeed(aSpeedRequested, DIRECTION_FORWARD);
    }
}
void PWMDcMotor::setSpeedCompensated(int aRequestedSpeed) {
    uint8_t tDirection;
    if (aRequestedSpeed > 0) {
        tDirection = DIRECTION_FORWARD;
    } else {
        tDirection = DIRECTION_BACKWARD;
        aRequestedSpeed = -aRequestedSpeed;
    }
    setSpeedCompensated(aRequestedSpeed, tDirection);
}

/*
 * First set PWM to 0 then disable driver
 * aStopMode can be: MOTOR_BRAKE or MOTOR_RELEASE
 */
void PWMDcMotor::stop(uint8_t aStopMode) {
    CurrentSpeed = 0;
    MotorValuesHaveChanged = true;
    MotorMovesFixedDistance = false;
#ifdef USE_FULL_BRIDGE_BREAKOUT_BOARD
    analogWrite(PWMPin, 0);
#else
#  ifdef USE_OWN_LIBRARY_FOR_ADAFRUIT_MOTOR_SHIELD
    setSpeed(0, DIRECTION_FORWARD);
#  else
    Adafruit_MotorShield_DcMotor->setSpeed(0);
#  endif
#endif
    setMotorDriverMode(CheckStopMODE(aStopMode));
}

/*
 * Not used yet
 * @param aStopMode used for speed == 0. One of: MOTOR_BRAKE or MOTOR_RELEASE
 */
void PWMDcMotor::setStopMode(uint8_t aStopMode) {
    StopMode = CheckStopMODE(aStopMode);
}

/******************************************************************************************
 * Distance functions
 *****************************************************************************************/
#define SPEED_DISTANCE_FACTOR 1.4
/*
 * @param aDistanceCount distance in 5mm resolution
 */
void PWMDcMotor::initGoDistanceCount(uint16_t aDistanceCount, uint8_t aRequestedDirection) {
    setSpeedCompensated(MaxSpeed, aRequestedDirection);
    /*
     * Estimate duration
     */
    computedMillisOfMotorStopForDistance = millis() + 50 + aDistanceCount * (MaxSpeed - MinSpeed) * SPEED_DISTANCE_FACTOR;
    MotorMovesFixedDistance = true;
}

/*
 * Not used yet
 */
void PWMDcMotor::initGoDistanceCount(int16_t aDistanceCount) {
    uint8_t tRequestedDirection = DIRECTION_FORWARD;

    if (aDistanceCount < 0) {
        aDistanceCount = -aDistanceCount;
        tRequestedDirection = DIRECTION_BACKWARD;
    }
    initGoDistanceCount(aDistanceCount, tRequestedDirection);
}

/*
 * @return true if not stopped (motor expects another update)
 */
bool PWMDcMotor::updateMotor() {
    if (MotorMovesFixedDistance && CurrentSpeed != 0 && millis() > computedMillisOfMotorStopForDistance) {
        stop(StopMode);
        return false;
    }
    return true;
}

/******************************************************************************************
 * EEPROM functions
 *****************************************************************************************/
/*
 * minSpeed (at which car starts to move) for 8 volt is appr. 35 to 40, for 4.3 volt (USB supply) is appr. 90 to 100
 */
void PWMDcMotor::setEepromMotorValuesDefaults() {
    MinSpeed = DEFAULT_MIN_SPEED;
    MaxSpeed = DEFAULT_MAX_SPEED;
    SpeedCompensation = 0;
}

void PWMDcMotor::readMotorValuesFromEeprom() {
    EepromMotorInfoStruct tEepromMotorInfo;
    eeprom_read_block((void*) &tEepromMotorInfo, (void*) (MotorNumber * sizeof(EepromMotorInfoStruct)),
            sizeof(EepromMotorInfoStruct));
    /*
     * Plausibility check for values
     */
    setEepromMotorValuesDefaults();
    if (tEepromMotorInfo.MinSpeed < 100) {
        MinSpeed = tEepromMotorInfo.MinSpeed;
    }
    if (tEepromMotorInfo.MaxSpeed > 40) {
        MaxSpeed = tEepromMotorInfo.MaxSpeed;
    }
    if (tEepromMotorInfo.SpeedCompensation < 24) {
        SpeedCompensation = tEepromMotorInfo.SpeedCompensation;
    }
    MotorValuesHaveChanged = true;
}

void PWMDcMotor::writeMotorvaluesToEeprom() {
    EepromMotorInfoStruct tEepromMotorInfo;
    tEepromMotorInfo.MinSpeed = MinSpeed;
    tEepromMotorInfo.MaxSpeed = MaxSpeed;
    tEepromMotorInfo.SpeedCompensation = SpeedCompensation;

    eeprom_write_block((void*) &tEepromMotorInfo, (void*) (MotorNumber * sizeof(EepromMotorInfoStruct)),
            sizeof(EepromMotorInfoStruct));
}
