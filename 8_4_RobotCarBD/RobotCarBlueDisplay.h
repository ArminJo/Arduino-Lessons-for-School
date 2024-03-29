/*
 * RobotCarBlueDisplay.h
 *
 *  Copyright (C) 2022  Armin Joachimsmeyer
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
 *  along with this program. If not, see <http://www.gnu.org/licenses/gpl.html>.
 */

#ifndef _ROBOT_CAR_BLUE_DISPLAY_H
#define _ROBOT_CAR_BLUE_DISPLAY_H

#if defined(MONITOR_VIN_VOLTAGE)
#define VOLTAGE_LIPO_LOW_THRESHOLD          6.9 // Formula: 2 * 3.5 volt - voltage loss: 25 mV GND + 45 mV VIN + 35 mV Battery holder internal
#define VOLTAGE_USB_THRESHOLD               5.5
#define VOLTAGE_USB_THRESHOLD_MILLIVOLT     5500 // required for preprocessor condition
#define VOLTAGE_TOO_LOW_DELAY_ONLINE        3000 // display VIN every 500 ms for 4 seconds
#define VOLTAGE_TOO_LOW_DELAY_OFFLINE       1000 // wait for 1 seconds after double beep
#endif

int doUserCollisionDetection();

#endif // _ROBOT_CAR_BLUE_DISPLAY_H
