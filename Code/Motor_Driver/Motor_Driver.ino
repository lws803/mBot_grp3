#include "MeOrion.h"
#include <PID_v1.h>

MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

uint8_t motorSpeedL = 100;
uint8_t motorSpeedR = 100;

double Output, Output2, Input, Input2, Setpoint, Setpoint2;

PID myPID(&Input, &Output, &Setpoint,1,0,0, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, 3, 0, 0, DIRECT);


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
  Setpoint = 430; // Above this value it will set output to 0, need to account for default resistance of circuit 
  Setpoint2 = 80; // Right sensor
  // Turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);
  Serial.begin(9600);

}

void loop()
{
  // PID controls
  Input = analogRead(0); // Left - value gets higher when it gets closer 
  Input2 = analogRead(3); // Right - value gets higher when it gets closer 
 
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
  
  // Motor controls  
  motorL.run(-Output/3 - 100);
  motorR.run(Output2 + 100);
}

