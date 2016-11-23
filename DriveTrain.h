/*
 * DriveTrain.h
 * 
 * Copyright 2016 Bill Williams <wlwilliams1952@gmail.com, github/BillWilliams1952>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef __DRIVETRAIN_H__

#define __DRIVETRAIN_H__

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define USE_DEFAULT_SPEED		(byte)0

typedef enum direction_t { RUN_FORWARD=0, RUN_BACKWARD, TURN_LEFT, TURN_RIGHT } direction;

class DriveTrain {
	
	public:
		DriveTrain ( byte leftMotor, byte rightMotor );
		void Begin ( void );
		void Run ( direction dir, byte speed = USE_DEFAULT_SPEED, boolean doDelay = true );
		void Stop ( void );
	
	private:
		Adafruit_MotorShield AFMS;
		Adafruit_DCMotor *leftWheel, *rightWheel;
		byte motorSpeed, leftMotorNum, rightMotorNum;
		byte defaultSpeeds[4] = { 100, 80, 30, 30 };
};


#endif
