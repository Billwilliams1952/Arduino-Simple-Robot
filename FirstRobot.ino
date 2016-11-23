/* 
*/

#include "Scanner.h"
#include "DriveTrain.h"

#define LEFT_WHEEL                1     // M1 thru M4 on shield
#define RIGHT_WHEEL               2
#define SERVO_CONTROL_PIN         10       // Default 10 is S1, 9 is S2
#define TRIG_PIN                  7    // For HC-SR04 ultrasonic sensor  WHITE
#define ECHO_PIN                  6    // YELLOW
#define SOUND_PIN                 8
#define HEARTBEAT                 13
#define DEFAULT_FWD_ANGLE         100    // 90 seems a bit off

Scanner scanner ( SERVO_CONTROL_PIN, TRIG_PIN, ECHO_PIN, DEFAULT_FWD_ANGLE );

DriveTrain dt ( LEFT_WHEEL, RIGHT_WHEEL );

void RandomWalk ( void ) {
    static int walkInterval = 0;
    static byte motorSpeed; // -1 INIT, 0 Forward, 1 backward, 2 rotate left, 3 rotate right
    static unsigned long timer;
    static direction walkType = (direction)255;
  
    if ( walkType == (direction)255 ) {
      timer = millis();
      delay(1000);
    }
  
    if ( millis() - timer >= (unsigned)walkInterval ) {
      dt.Stop();
      delay(1000);
      walkType = (direction)random(RUN_FORWARD,TURN_RIGHT+1);
      walkInterval = random(500,5001);
      motorSpeed = random(40,200);    // max 255
  
      timer = millis();

      dt.Run(walkType,walkType < TURN_LEFT ? motorSpeed : 0);
    }
}


void setup() {
    byte on;
  
    Serial.begin(9600);

    scanner.Begin(); 
     
    dt.Begin();

    pinMode(HEARTBEAT,OUTPUT);
    pinMode(SOUND_PIN,OUTPUT);

    // Announce we're ready.....
    for ( byte i = 0; i < 21; i++ ) {
      on = i % 2 ? HIGH : LOW;
      digitalWrite(SOUND_PIN,on);
      digitalWrite(HEARTBEAT,!on);
      delay(500 - i*20);     
    }
    
}

void loop() {
    typedef enum states_t { _INIT, _PREP_FWD, _FWD, _PREP_BACK, _BACK, _PREP_LEFT, _LEFT, 
                         _PREP_RIGHT, _RIGHT, _PREP_STUCK, _STUCK, _PREP_SCAN, _SCAN } states;

    static states state = _PREP_SCAN;
    static unsigned int distance;

    digitalWrite(HEARTBEAT,(millis() % 1000) > 500 ? HIGH : LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

    switch ( state ) {
        case _INIT: 
            state = _PREP_FWD;
            break;

        case _PREP_FWD:
            scanner.SlewToAngle(DEFAULT_FWD_ANGLE);
            dt.Run(RUN_FORWARD);
            state = _FWD;
            break;

        case _FWD:
            if ( ! scanner.DistanceOK() ) {
                state = _PREP_SCAN;
            }
            break;

        case _PREP_BACK:
            scanner.SlewToAngle(DEFAULT_FWD_ANGLE);
            dt.Run(RUN_BACKWARD);
            state = _BACK;
            break;

        case _BACK:
            if ( scanner.DistanceOK(24) ) {
                state = _PREP_SCAN;
            }         
            break;

        case _PREP_LEFT:
            dt.Run(TURN_LEFT);
            state = _LEFT;
            break;

        case _LEFT:
            if ( scanner.DistanceOK ( (byte)(0.9 *  distance)) ) {
                state = _PREP_FWD;                
            }     
            break;

        case _PREP_RIGHT:
            dt.Run(TURN_RIGHT);
            state = _RIGHT;
            break;

        case _RIGHT:
            if ( scanner.DistanceOK ((byte)(0.9 * distance)) ) {
                state = _PREP_FWD;                
            }
            break;

        case _PREP_SCAN:
            dt.Stop();
            scanner.SetupScan();
            state = _SCAN;
            break;

        case _SCAN:
            if ( scanner.RunScan() ) {
                // scan complete, check maxDistance
                distance = scanner.GetScanMaxDistance();
//                if ( distance > 24 ) {
//                    state = scanner.GetScanAngleAtMaxDistance() < 90 ? _PREP_LEFT : _PREP_RIGHT;
//                }
//                else {
//                    // maybe not enough room... lets backup a bit
//                    state = _PREP_BACK;
//                }
            state = _PREP_SCAN;
            }
            delay(50);
            break;

        case _PREP_STUCK:
            break;

        case _STUCK:
            break;
    }
}
