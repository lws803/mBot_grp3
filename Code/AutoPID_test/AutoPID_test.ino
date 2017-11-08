#include "MeOrion.h"
#include <PID_v1.h>
#define IR_SIDE_L A1
#define IR_SIDE_R A0

#define runMotor 1

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

double outputL, outputR, inputL, inputR, setpointL, setpointR; 

double aggKp_l=3, aggKi_l=0, aggKd_l=1;

double consKp_l=1, consKi_l=0.2, consKd_l=0;

double aggKp_r=3.5, aggKi_r=0, aggKd_r=1;

double consKp_r=1, consKi_r=0.2, consKd_r=0;

PID myPID_L(&inputL, &outputL, &setpointL,consKp_l,consKi_l,consKd_l, DIRECT); // Maybe increase the integral to make it smoother 
PID myPID_R(&inputR, &outputR, &setpointR,consKp_r,consKi_r,consKd_r, DIRECT);

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
  setpointL = left_sum/10;
  setpointR = right_sum/10;

  Serial.begin (9600);

}

void loop() {
    inputL = analogRead(IR_SIDE_L)  ;
    inputR = analogRead (IR_SIDE_R) ;

    double gap_l = abs(setpointL-inputL); //distance away from setpoint
    if(gap_l<10)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID_L.SetTunings(consKp_l, consKi_l, consKd_l);
    }
    else
    {
     //we're far from setpoint, use aggressive tuning parameters
      myPID_L.SetTunings(aggKp_l, aggKi_l, aggKd_l);
    }

    double gap_r = abs(setpointR-inputR); //distance away from setpoint
    if(gap_r<10)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID_R.SetTunings(consKp_r, consKi_r, consKd_r);
    }
    else
    {
     //we're far from setpoint, use aggressive tuning parameters
      myPID_R.SetTunings(aggKp_r, aggKi_r, aggKd_r);
    }

    myPID_L.Compute();
    myPID_R.Compute();
    // Motor controls
    switch (runMotor) {
      case 1: 
      motorL.run(-(140 + outputL/2));
      motorR.run(140 + outputR/2);
      break;
      case 0:
      Serial.print (outputL);
      Serial.print (" ");
      Serial.println(outputR);
      break;
    }
    delay (100);
}
