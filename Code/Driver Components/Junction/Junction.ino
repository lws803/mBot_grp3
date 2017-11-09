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

int blackLine() {
  int blackL = digitalRead(IR_DOWN_L);
  int blackR = digitalRead(IR_DOWN_R);
  Serial.print("Downward IR left pin: ");
  Serial.print(blackL);
  Serial.print("\tDownward IR right pin: ");
  Serial.println(blackR);
  if(blackL || blackR) return 0;
  else return 1;
}

void setup()
{
  Serial.begin (9600);
}
void loop()
{
  int f = blackLine();
  Serial.print("Value returned by blackLine() function: ");
  Serial.println(f);
  Serial.println("\n");
  if(f) wait();
  delay(5000);
}
