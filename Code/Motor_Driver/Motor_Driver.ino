#include "MeOrion.h"
#include <PID_v1.h>

MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

uint8_t motorSpeedL = 255;
uint8_t motorSpeedR = 255;

double Output, Output2, Input, Input2, Setpoint, Setpoint2;

PID myPID(&Input, &Output, &Setpoint,1,0,0, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, 1, 0, 0, DIRECT);


//stand by for some time
void statically(int duration) {
  motorL.stop();
  motorR.stop();
  delay(duration);
}
//moving speed: cm/ms, used to calculate moving time
void forward(int duration) {
  motorL.run(-motorSpeedL);
  motorR.run(motorSpeedR);
  delay(duration);
}
//moving speed: cm/ms, used to calculate moving time
void backward(int duration) {
  motorL.run(motorSpeedL);
  motorR.run(-motorSpeedR);
  delay(duration);
}
//time required for turning: ms
void left() {
  motorL.run(motorSpeedL);
  motorR.run(motorSpeedR);
  delay(716);
}
//time required for turning: ms
void right() {
  motorL.run(-motorSpeedL);
  motorR.run(-motorSpeedR);
  delay(717);
}

void setup()
{
  // PID controls
  Setpoint = 550; // LED will turn on whenever LDR falls below 100
  Setpoint2 = 550;
  // Turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop()
{
  // PID controls
  Input = analogRead(0); // Left
  Input2 = analogRead(1); // Right
  
  int output_int = Output; // Left
  int output2_int = Output2; // Right
  
  myPID.Compute();
  myPID2.Compute();

  
  /**
  statically(4000);
  left();
  statically(2000);
  right();
  statically(4000);
  */
  Serial.print("Left: ");
  Serial.println (Input);
  Serial.print("Right: ");
  Serial.println (Input2);
  
  // Motor controls
  motorL.run(-motorSpeedL + output_int);
  motorR.run(motorSpeedR - output2_int);
  delay(100);
}

