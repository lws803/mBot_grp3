#include "MeOrion.h"
#include <PID_v1.h>
#define IR_SIDE_L A1
#define IR_SIDE_R A0

#define runMotor 1

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

double outputL, outputR, inputL, inputR, setpointL, setpointR; 

PID myPID_L(&inputL, &outputL, &setpointL,1,1,2, DIRECT);
PID myPID_R(&inputR, &outputR, &setpointR,1,1,2, DIRECT);

void setup() {
  setpointL = 630;
  setpointR = 630;
  myPID_L.SetMode(AUTOMATIC);
  myPID_R.SetMode(AUTOMATIC);
  Serial.begin (9600);
}

void loop() {
    inputL = analogRead(IR_SIDE_L);
    inputR = analogRead (IR_SIDE_R);

    myPID_L.Compute();
    myPID_R.Compute();
    // Motor controls
    switch (runMotor) {
      case 1: 
      motorL.run(-(outputL + 140));
      motorR.run(outputR + 140);
      break;
      case 0:
      Serial.print (outputL);
      Serial.print (" ");
      Serial.println(outputR);
      break;
    }
}
