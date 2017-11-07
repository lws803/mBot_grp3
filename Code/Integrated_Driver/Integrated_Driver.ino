#include "MeOrion.h"
#include "PID_v1.h"

#define TIMEOUT 30000
#define ULTRASONIC_SENSOR_PIN 10
#define DOWN_IR1 11
#define DOWN_IR2 12

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);
uint8_t motorSpeedL = 100;
uint8_t motorSpeedR = 100;

// PID setups
double Output, Output2, Input, Input2, Setpoint, Setpoint2;
PID myPID(&Input, &Output, &Setpoint,1, 0, 0, DIRECT);
PID myPID2(&Input2, &Output2, &Setpoint2, 3, 0, 0, DIRECT);

// Raw driving functions
void statically(int duration) {
  motorL.stop();
  motorR.stop();
  delay(duration);
}
void forward(int duration) {
  motorL.run(-motorSpeedL);
  motorR.run(motorSpeedR);
  delay(duration);
}
void backward(int duration) {
  motorL.run(motorSpeedL);
  motorR.run(-motorSpeedR);
  delay(duration);
}
void left() {
  motorL.run(motorSpeedL);
  motorR.run(motorSpeedR);
  delay(716);
}
void right() {
  motorL.run(-motorSpeedL);
  motorR.run(-motorSpeedR);
  delay(717);
}

double echolocation() {
  long duration;
  double distance;
  
  pinMode(ULTRASONIC_SENSOR_PIN, OUTPUT);
  digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
  pinMode(ULTRASONIC_SENSOR_PIN, INPUT);
  duration = pulseIn(ULTRASONIC_SENSOR_PIN, HIGH, TIMEOUT);
  distance = duration / 2.0 * 0.034;
  
  Serial.print("Distance to the front wall: ");
  Serial.println(distance);  
  return distance;  
}

int blackLine() {
  int black1 = digitalRead(DOWN_IR1);
  int black2 = digitalRead(DOWN_IR2);
  Serial.print("Value of left pin: ");
  Serial.print(black1);
  Serial.print("\tValue of right pin: ");
  Serial.println(black2);
  if(black1 || black2) return 0;
  else return 1;
}

void setup()
{
  // PID controls, above this value it will set output to 0
  Setpoint = 430; // Left sensor
  Setpoint2 = 80; // Right sensor
  // Turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID2.SetMode(AUTOMATIC);
  
  Serial.begin(9600);
}

void loop()
{
  // Read voltage values across IR receivers
  Input = analogRead(A0); // Left - value gets lower when it gets closer
  Input2 = analogRead(A3); // Right - value gets lower when it gets closer
  
  double d = echolocation();
  
  if(blackLine()) {
    statically(5000); // To be modified
  }

  else if(d < 10.0) {
    if(Input > 600 && Input2 > 450); // Keep going forward and wait for the black line to be detected
    else if(Input > 600) left(); // Only left side is empty
    else if(Input2 > 450) right(); // Only right side is empty
    // Else it is a failure of the ultrasonic sensor
  }

  else {
    // Computation of PID outputs
    myPID.Compute();
    myPID2.Compute();
  
    Serial.print("Left: ");
    Serial.print(Input);
    Serial.print(", ");
    Serial.print(Output);
    Serial.print("\tRight: ");
    Serial.print(Input2);
    Serial.print(", ");
    Serial.println(Output2);
    
    // Motor controls  
    motorL.run(-Output/3 - 100);
    motorR.run(Output2 + 100);
  }
}
