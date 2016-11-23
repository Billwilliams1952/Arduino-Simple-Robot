/*
 * DriveTrain.cpp
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


#include "DriveTrain.h"

DriveTrain :: DriveTrain ( byte leftMotor, byte rightMotor ) {
	leftMotorNum = leftMotor;
	rightMotorNum = rightMotor;
}
void DriveTrain :: Begin ( void ) {
	AFMS = Adafruit_MotorShield();
	leftWheel = AFMS.getMotor(leftMotorNum);
	rightWheel = AFMS.getMotor(rightMotorNum);
	
	AFMS.begin();
}

void DriveTrain :: Run ( direction dir, byte speed, boolean doDelay ) {
	//Stop();
	if ( speed != USE_DEFAULT_SPEED ) {
		leftWheel->setSpeed(speed);
		rightWheel->setSpeed(speed);
	}
	else {    
		leftWheel->setSpeed(defaultSpeeds[dir]);
		rightWheel->setSpeed(defaultSpeeds[dir]);
	}
	switch ( dir ) {
		case RUN_FORWARD:
			leftWheel->run(FORWARD);
			rightWheel->run(FORWARD);
			break;
		case RUN_BACKWARD:
			leftWheel->run(BACKWARD);
			rightWheel->run(BACKWARD);
			break;
		case TURN_LEFT:
			leftWheel->run(FORWARD);
			rightWheel->run(BACKWARD);
			break;
		case TURN_RIGHT:
			leftWheel->run(BACKWARD);
			rightWheel->run(FORWARD);
			break;
			
	}
	if ( doDelay ) delay ( 200 );
}

void DriveTrain :: Stop ( void ) {
	leftWheel->run(RELEASE);
	rightWheel->run(RELEASE);
}

