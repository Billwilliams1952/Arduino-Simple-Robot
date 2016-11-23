# Arduino-Simple-Robot

A simple Arduino sketch for controlling a small two wheel robot. The robot wheels are drive my an Adafruit motorshield. An ultrasonic sensor attached to the front and driven by a servo provides range detection over 180 degrees forward field of view. 

## Synopsis

This is my first attempt at creating a small inexpensive autonomous robot.

## Installation

Download the ZIP file and extract into your **sketchbook** directory.

## API Reference

This program uses the Arduino API (**Arduino.h**, **spi.h** and **wire.h**) and two libraries for driving the motor shield - **Adafruit_MotorShield** and **Adafruit_MS_PWMServoDriver**. It has been tested on the **Arduino Uno**.

## Tests

No special tests are provided. Let the robot run until it:
- gets stuck in a rut
- gets stuck against a wall
- gets caught under furniture
- runs out of power

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.
