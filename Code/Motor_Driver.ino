#include "MeOrion.h"

MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

uint8_t motorSpeedL = 100;
uint8_t motorSpeedR = 100;

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
}

void loop()
{
  statically(4000);
  left();
  statically(2000);
  right();
  statically(4000);
}

