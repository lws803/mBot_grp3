#include "MeOrion.h"

// Sensor setups
#define BUZZER 8
#define LIGHT A6
#define SOUND A3
#define TIMEOUT 30000
#define ULTRASONIC 10
#define IR_DOWN_L 11
#define IR_DOWN_R 12
#define IR_SIDE_L A1
#define IR_SIDE_R A0

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);
// Raw driving functions
void wait() {
  motorL.stop();
  motorR.stop();
}
void go() {
  motorL.run(-100);
  motorR.run(100);
  delay(1000);
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

double echolocation() {
  int timeout = 30000;
  double duration;
  double distance;
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, LOW);
  pinMode(ULTRASONIC, INPUT);
  duration = pulseIn(ULTRASONIC, HIGH, timeout);
  distance = duration / 2.0 * 0.034;
  Serial.print("\n\nDuration for dual distance to the front wall: ");
  Serial.println(distance);
  Serial.print("Distance to the front wall: ");
  Serial.println(distance);
  return distance;  
}

void setup()
{
  Serial.begin (9600);
}
void loop()
{
  int f = blackLine();
  if(f < 10.0) wait();
  delay(5000);
}
