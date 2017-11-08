#include "AutoPID.h"
#include "MeOrion.h"

#define IR_SIDE_L A1
#define IR_SIDE_R A0
#define setpointL  600
#define setpointR 450
#define OUTPUT_MIN 50
#define OUTPUT_MAX 50

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

double outputL, outputR, inputL, inputR, 
AutoPID myPID_left(&inputL, &setPoint, &outputL, OUTPUT_MIN, OUTPUT_MAX, 1, 1, 2);
AutoPID myPID_right(&inputR, &setPoint, &outputR, OUTPUT_MIN, OUTPUT_MAX, 1, 1, 2);


void setup() {
  Serial.begin (9600);
}

void loop() {
    inputL = analogRead(IR_SIDE_L);
    inputR = analogRead (IR_SIDE_R);
    myPID_left.run();
    myPID_right.run();

    Serial.print (inputL);
    Serial.print (" ");
    Serial.print (inputR);
    
    // Motor controls
    motorL.run(-(outputL + 140));
    motorR.run(outputR + 140);
    
  
}
