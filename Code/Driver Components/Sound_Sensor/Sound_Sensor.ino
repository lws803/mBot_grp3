#include "MeOrion.h"

// Pins
#define BUZZER 8
#define LIGHT A6
#define SOUND A3
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

int soundChallenge() {
  double average = 0, v;
  for (int i = 0; i < 10; i++) {
    average += (double)analogRead(SOUND) / 1023.0 * 5.0;
    delay(50);
  }
  
  v = average/10;
  //Serial.print("Sound sensor feedback voltage: ");
  Serial.println(v);
  /*
  if(v >= 0.0 && v < 1.0) return 0;
  else if(v >= 1.0 && v < 2.3) { right(); go(); }
  else if(v >= 2.3 && v < 5.0) { left(); go(); }
  */
  return 1;
}

void setup() {
  Serial.begin (9600);
}

void loop() {
  int f = soundChallenge();
  /*
  Serial.print("Value returned by soundChallenge() function: ");
  Serial.println(f);
  */
  //motorL.run(255);
  //motorR.run(255);
}
