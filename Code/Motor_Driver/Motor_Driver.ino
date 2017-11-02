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
  Setpoint = 800; // Above this value it will set output to 0, need to account for default resistance of circuit 
  Setpoint2 = 800;
  // Turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop()
{
  // PID controls
  Input = analogRead(0); // Left - value gets higher when it gets closer 
  Input2 = analogRead(1); // Right - value gets higher when it gets closer 
  
  int output_int = Output; // Left
  int output2_int = Output2; // Right


  // Stud test: 
  //Input = 700;
   
  myPID.Compute();
  myPID2.Compute();

  Serial.print("Left: ");
  Serial.print(" ");
  Serial.print (Input);
  Serial.print(" ");
  Serial.print (Output);
  Serial.print(" ");
  Serial.print("Right: ");
  Serial.print ("");
  Serial.print (Input2);
  Serial.print(" ");
  Serial.println (Output2);
  Serial.print ("Motor_left: ");
  Serial.print (output2_int);
  Serial.print (" ");
  Serial.print ("Motor_right: ");
  Serial.println (output_int);
  
  // Motor controls  
  //motorL.run(-output2_int);
  //motorR.run(output_int);
}

