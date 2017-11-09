#include "MeOrion.h"
#include "PID_v1.h"
#define IR_SIDE_L A1
#define IR_SIDE_R A0
#define ULTRASONIC_SENSOR 10
#define TIMEOUT 30000

#define runMotor 0

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

int count = 0;
double outputL, outputR, inputL, inputR, setpointL, setpointR; 

//double aggKp_l=3, aggKi_l=0, aggKd_l=1;

double consKp_l=1, consKi_l=0.2, consKd_l=0;

//double aggKp_r=3, aggKi_r=0, aggKd_r=1;

double consKp_r=1, consKi_r=0.2, consKd_r=0;

PID myPID_L(&inputL, &outputL, &setpointL,consKp_l,consKi_l,consKd_l, DIRECT); 
PID myPID_R(&inputR, &outputR, &setpointR,consKp_r,consKi_r,consKd_r, DIRECT);

double echolocation() {
  double duration;
  double distance;
  pinMode(ULTRASONIC_SENSOR, OUTPUT);
  digitalWrite(ULTRASONIC_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR, HIGH);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR, LOW);
  pinMode(ULTRASONIC_SENSOR, INPUT);
  duration = pulseIn(ULTRASONIC_SENSOR, HIGH, TIMEOUT);
  distance = duration / 2.0 * 0.034;  
  return distance;  
}

void left() {
  motorL.run(130);
  motorR.run(130);
  delay(575);
}
void right() {
  motorL.run(-130);
  motorR.run(-130);
  delay(575);
}

void go() {
  motorL.run(-100);
  motorR.run(100);
  delay(1000);
}


void setup() {
  inputL = analogRead(IR_SIDE_L);
  inputR = analogRead (IR_SIDE_R);

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
    int d = echolocation();
    
    /*
    double gap_l = abs(setpointL-inputL); //distance away from setpoint
    if(gap_l<10)
    {  //we're close to setpoint, use conservative tuning parameters
      //myPID_L.SetTunings(consKp_l, consKi_l, consKd_l);
    }
    else
    {
     //we're far from setpoint, use aggressive tuning parameters
      //myPID_L.SetTunings(aggKp_l, aggKi_l, aggKd_l);
    }

    double gap_r = abs(setpointR-inputR); //distance away from setpoint
    if(gap_r<10)
    {  //we're close to setpoint, use conservative tuning parameters
      //myPID_R.SetTunings(consKp_r, consKi_r, consKd_r);
    }
    else
    {
     //we're far from setpoint, use aggressive tuning parameters
      //myPID_R.SetTunings(aggKp_r, aggKi_r, aggKd_r);
    }
    */
    
    myPID_L.Compute();
    myPID_R.Compute();
    // Motor controls
    switch (runMotor) {
      case 1: 
      motorL.run(-(140 + outputL/2));
      motorR.run(140 + outputR/2);
      break;
      case 0:
      Serial.print (inputL);
      Serial.print (" ");
      Serial.println(inputR);
      break;
    }
}
