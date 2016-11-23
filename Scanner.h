/*
 * Scanner.h
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

#ifndef __SCANNER_H__

#define __SCANNER_H__

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <HCSR04.h>

class Scanner {
	
	public:
		Scanner ( byte servoPin, byte trigPin, byte echoPin, 
				  byte defaultFwdAngle, byte minDistance = 10 );
		void Begin ( void );
		void SetupScan ( void );
		boolean RunScan ( void );		// true when complete
		unsigned int GetCurrentDistance ( void );
		boolean DistanceOK ( byte minDist = 0 );
		unsigned int GetScanMaxDistance ( void );
		byte GetScanAngleAtMaxDistance ( void );
		void SlewToAngle ( byte angle );
		void TestServo ( void );
	
	private:
		HCSR04 *distSensor;
		unsigned int maxDistance, temp;
		Servo distanceSensorServo;
		int angle;
		byte defaultFwdAngle, currentAngle, angleAtMax, servoPin, minDistance;
};

#endif
