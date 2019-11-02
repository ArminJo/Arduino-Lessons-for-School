# Arduino lessons for school
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https%3A%2F%2Fgithub.com%2FArminJo%2FArduino-Lessons-for-School)](https://github.com/brentvollebregt/hit-counter)

These lessons are for my course at a Gymnasium in Cologne. The course is addressed at eighth or ninth grade pupils.<br/> 
I use the [Sloeber IDE](http://eclipse.baeyens.it/) here, since it is as easy as the Arduino IDE but a lot more powerful and flexible.
All examples will also run with the Arduino IDE, just copy the program file content to a new sketch.<br/> 
Each lesson consists of the `.cpp file` the pupils work with, a `.task file` with the original content of the task, and a `Solution.cpp` file where the complete solution is contained.<br/>
All lessons work on a universal breadboard layout, and can easily be adapted by just changing the `Breadboard.h` file of the examples.

# Sloeber installation
My sloeber is installed at `E:\Elektro\sloeber`, so it will work out of the box if you use the same location. If you have no E: drive you can use the command subst E: "C:<Path to sloeber root directory>"<br/>
To easy import the examples you must check under `Arduino/Preferences/Arduino/Platform and Boards/arduino/Arduino AVR Boards` if version `1.8.1` is available and checked.
If it is not available, you have to check `Update local json files` in `Arduino/Preferences/Arduino/Third party index url's` and then restart sloeber and check the `1.8.1` entry.<br/>
If `File/Import/General/Existing Projects into Workspace` does not work, just can create a new Arduino project and choose `default cpp file`. Then copy the content of the lesson to the new cpp file.

## Universal breadboard layout for lessons
![Universal breadboard front](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Front.jpg)
![Universal breadboard top](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Top.jpg)
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Back.jpg)
