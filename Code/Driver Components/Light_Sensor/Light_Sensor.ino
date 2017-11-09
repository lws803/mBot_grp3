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

int lightChallenge() {
  double v = (double)analogRead(LIGHT) / 1023.0 * 5.0;
  Serial.print("Light sensor voltage reading: ");
  Serial.println(v);
  if(v >= 0.0 && v < 1.3) return 0;
  else if(v >= 1.3 && v < 2.6) { right(); go(); }
  else if(v >= 2.6 && v < 3.9) { left(); go(); }
  else if(v >= 3.9 && v < 5.0) { go(); }
  return 1;
}

void setup()
{
  Serial.begin (9600);
}
void loop()
{
  int f = lightChallenge();
  Serial.print("Value returned by lightChallenge() function: ");
  Serial.println(f);
  Serial.println("\n");
}
