/*
 * Scanner.cpp
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

#include "Scanner.h"

Scanner :: Scanner ( byte servoPin, byte trigPin, byte echoPin, byte defaultFwdAngle, 
					 byte minDistance ) {
	distSensor = new HCSR04 (trigPin,echoPin);

	this->defaultFwdAngle = defaultFwdAngle;
	this->servoPin = servoPin;
	this->minDistance = minDistance;
	currentAngle = defaultFwdAngle;
}

void Scanner :: Begin ( void ) {
	distanceSensorServo.attach(servoPin);  // attaches the servo to the pin
	SlewToAngle(defaultFwdAngle);
}

unsigned int Scanner :: GetCurrentDistance ( void ) {
	return distSensor->GetDistanceInInches();
}

boolean Scanner :: DistanceOK ( byte minDist ) {
	int dist = GetCurrentDistance();
	if ( minDist == 0 )
		minDist = minDistance;
	return (dist == 0) || (dist >= minDist);
}

void Scanner :: SlewToAngle ( byte angle ) {
	if ( angle > 180 )
		angle = 180;
	distanceSensorServo.write(angle);
}

void Scanner :: SetupScan ( void ) {
	currentAngle = defaultFwdAngle;
	maxDistance = 0;
	//for ( angle = currentAngle; angle >= 0; angle-- ) {
		//distanceSensorServo.write(angle);
		//delay(10);
	//}
	distanceSensorServo.write(0);
	delay(500);
	angle = 0;
	maxDistance = 0;
}

void Scanner :: TestServo ( void ) {
	int pos;
	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		distanceSensorServo.write(pos);   // tell servo to go to position in variable 'pos'
		delay(15);                        // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		distanceSensorServo.write(pos);   // tell servo to go to position in variable 'pos'
		delay(15);                        // waits 15ms for the servo to reach the position
	};
}

boolean Scanner :: RunScan ( void ) {
	/*
	 * This function is setup to be called continuously. Returing True
	 * when scan is complete
	*/
	distanceSensorServo.write(angle);
	delay(100);
	temp = distSensor->GetDistanceInInches();
	if ( temp > maxDistance ) {
		maxDistance = temp;
		angleAtMax = angle;
	}
	angle += 5;
	if ( angle > 180 ) {
		SlewToAngle(defaultFwdAngle);
		return true;
	}
	return false;
}

unsigned int Scanner :: GetScanMaxDistance ( void ) {
	return maxDistance;
}

byte Scanner :: GetScanAngleAtMaxDistance ( void ) {
	return angleAtMax;
}
