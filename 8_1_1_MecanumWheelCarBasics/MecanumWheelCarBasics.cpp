/*
 *  MecanumWheelCar.cpp
 *  Example for possible movements of a mecanum 4 wheel car
 */

#include <Arduino.h>

/*
 * You will need to change these values according to your motor, H-bridge and motor supply voltage.
 * You must specify this before the include of "MecanumWheelCarPWMMotorControl.hpp"
 */
//#define USE_ADAFRUIT_MOTOR_SHIELD   // Use Adafruit Motor Shield v2 connected by I2C instead of TB6612 or L298 breakout board.
#define VIN_2_LIPO                  // Activate this, if you use 2 LiPo Cells (around 7.4 volt) as Motor supply.
//#define VIN_1_LIPO                  // Or if you use a Mosfet bridge (TB6612), 1 LIPO (around 3.7 volt) may be sufficient.
//#define FULL_BRIDGE_INPUT_MILLIVOLT   6000  // Default. For 4 x AA batteries (6 volt).
#define MOSFET_BRIDGE_USED          // Activate this, if you use a (recommended) mosfet bridge instead of a L298 bridge, which has higher losses.
//#define DEFAULT_DRIVE_MILLIVOLT       2000 // Drive voltage -motors default speed- is 2.0 volt
//#define DO_NOT_SUPPORT_RAMP         // Ramps are anyway not used if drive speed voltage (default 2.0 V) is below 2.3 V. Saves 378 bytes program space.
#define CAR_HAS_4_MECANUM_WHEELS

#include "RobotCarPinDefinitionsAndMore.h"

#include "PWMDcMotor.hpp"

PWMDcMotor frontLeftMotor;
PWMDcMotor frontRightMotor;
PWMDcMotor backLeftMotor;
PWMDcMotor backRightMotor;

#define DELAY_BETWEEN_MOVEMENTS 500
void setup() {
// initialize the digital pin as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_PWMMOTORCONTROL));

    /*
     * initialize motors
     */
    frontRightMotor.init(FRONT_RIGHT_MOTOR_FORWARD_PIN, FRONT_RIGHT_MOTOR_BACKWARD_PIN, MOTOR_PWM_PIN);
    frontLeftMotor.init(FRONT_LEFT_MOTOR_FORWARD_PIN, FRONT_LEFT_MOTOR_BACKWARD_PIN, MOTOR_PWM_PIN);
    backRightMotor.init(BACK_RIGHT_MOTOR_FORWARD_PIN, BACK_RIGHT_MOTOR_BACKWARD_PIN, MOTOR_PWM_PIN);
    backLeftMotor.init(BACK_LEFT_MOTOR_FORWARD_PIN, BACK_LEFT_MOTOR_BACKWARD_PIN, MOTOR_PWM_PIN);
    /*
     * Tone feedback for end of boot
     */
    tone(PIN_BUZZER, 2200, 100);
    frontRightMotor.setSpeedPWM(0); // Required only for one motor, since the speed pin is the same for all motors
    delay(2000);

    /*
     * do a square
     */
    Serial.println(F("Forward"));
    frontLeftMotor.setSpeedPWM(0); // Required only for one motor, since the speed pin is the same for all motors
    frontLeftMotor.setDirection(DIRECTION_FORWARD);
    frontRightMotor.setDirection(DIRECTION_FORWARD);
    backLeftMotor.setDirection(DIRECTION_FORWARD);
    backRightMotor.setDirection(DIRECTION_FORWARD);
    frontRightMotor.setSpeedPWM(MAX_SPEED_PWM / 2);
    delay(1000);
    frontRightMotor.setSpeedPWM(0);
    Serial.println(F("Stop"));

    delay(DELAY_BETWEEN_MOVEMENTS);

    Serial.println(F("Right"));
    frontRightMotor.setDirection(DIRECTION_BACKWARD);
    frontLeftMotor.setDirection(DIRECTION_FORWARD);
    backRightMotor.setDirection(DIRECTION_FORWARD);
    backLeftMotor.setDirection(DIRECTION_BACKWARD);
    frontRightMotor.setSpeedPWM(MAX_SPEED_PWM / 2);
    delay(1000);
    frontRightMotor.setSpeedPWM(0);
    Serial.println(F("Stop"));

    delay(2000);

    Serial.println(F("End of setup"));
}

void loop() {
    tone(PIN_BUZZER, 2200, 100);
    delay(10000);
}
