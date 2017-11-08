#include "MeOrion.h"
#include <PID_v1.h>
#define IR_SIDE_L A1
#define IR_SIDE_R A0

#define runMotor 1

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

double outputL, outputR, inputL, inputR, setpointL, setpointR; 

PID myPID_L(&inputL, &outputL, &setpointL,1,2,2, DIRECT); // Maybe increase the integral to make it smoother 
PID myPID_R(&inputR, &outputR, &setpointR,1,2,2, DIRECT);

void setup() {
  inputL = analogRead(IR_SIDE_L);
  inputR = analogRead (IR_SIDE_R);
  //setpointL = 650;
  //setpointR = 850;
  myPID_L.SetMode(AUTOMATIC);
  myPID_R.SetMode(AUTOMATIC);
  
  double left_sum = 0, right_sum = 0;
  delay(1000);
  for (int i = 0; i < 10; i++) {
    left_sum += inputL;
    right_sum += inputR;
    delay (100);
  }
  setpointL = left_sum/10 - 50;
  setpointR = right_sum/10 - 70;

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
