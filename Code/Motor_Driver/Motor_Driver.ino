#include "MeOrion.h"
#include <PID_v1.h>
#define TIMEOUT 30000
#define ULTRASONIC_SENSOR_PIN 12


MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

uint8_t motorSpeedL = 100;
uint8_t motorSpeedR = 100;

double Output, Output2, Input, Input2, Setpoint, Setpoint2;

int state = 0;

PID myPID(&Input, &Output, &Setpoint,1,0,0, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, 3, 0, 0, DIRECT);

/**
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
// DEPRECATED
*/
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

void pid_move_straight (uint8_t desired_spd) {
  // PID controls
  Input = analogRead(0); // Left - value gets higher when it gets closer 
  Input2 = analogRead(3); // Right - value gets higher when it gets closer 
 
  myPID.Compute();
  myPID2.Compute();

 /**
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
  */

  
  // Motor controls  
  motorL.run(-Output/3 - desired_spd);
  motorR.run(Output2 + desired_spd);
}

int encouter(void) {
  /**
   * 0 means no encounters 
   * 1 means encounter wall with ultrasonic sensor  
   * 2 means encouter black line 
   */
   pinMode(ULTRASONIC_SENSOR_PIN, OUTPUT);
   digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
   delayMicroseconds(2);
   digitalWrite(ULTRASONIC_SENSOR_PIN, HIGH);
   delayMicroseconds(2);
   digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
   pinMode(ULTRASONIC_SENSOR_PIN, INPUT);
   duration = pulseIn(ULTRASONIC_SENSOR_PIN, HIGH, TIMEOUT);
   distance = duration / 2.0 * 0.034;
   if(distance < 10.0) {
     state = 1;
     return 1; // Encounter wall
   }

  // Line detector 

  
  state = 0;
  return 0; // No encounters by default 
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
  while (!encounter()) {
    pid_move_straight(100);
  }
  // Stop motor
  motorL.run(0);
  motorR.run(0);

    
  // Check state and determine action if none, continue with loop
  switch (state) {
    case 1:
    // Ultrasonic-u desu  
    break;
    case 2:
    // Line detector desu 
    break;
  }
}





