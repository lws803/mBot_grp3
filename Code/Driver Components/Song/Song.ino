#include "MeOrion.h"
#include "notes.h"

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

// notes in the melody
int notes[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
  NOTE_E4, NOTE_F4, NOTE_G4, 0,
  NOTE_E4, NOTE_F4, NOTE_G4, 0,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_C4, NOTE_G3, NOTE_C4, 0,
  NOTE_C4, NOTE_G3, NOTE_C4, 0
};
// note durations: 4 = quarter note, 8 = eighth note, etc.
float noteDurations[] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  16/3.0, 16, 16/3.0, 16, 4, 4,
  16/3.0, 16, 16/3.0, 16, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4
};
int win() {
  for (int thisNote = 0; thisNote < (sizeof(notes) / sizeof(int)); thisNote++) {
    float noteDuration = 2000 / noteDurations[thisNote];
    float pauseBetweenNotes = noteDuration * 1.30;
    tone(BUZZER, notes[thisNote], noteDuration);
    delay(pauseBetweenNotes);
  }
  wait();
  while(1) {
    delay(1000);
  }
}

void setup()
{
  Serial.begin (9600);
}

void loop()
{
  win();
}
