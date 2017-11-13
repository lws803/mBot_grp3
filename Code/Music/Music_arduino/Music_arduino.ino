#include "notes.h"
#define BUZZER 8

// notes in the melody
int notes[] = { 
  NOTE_F5, NOTE_F5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4,
  NOTE_AS4, NOTE_AS4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_DS5,
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_DS5, NOTE_A4, NOTE_A4,
  NOTE_F5, NOTE_F5, NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_DS5, NOTE_AS4, NOTE_AS4,
  NOTE_C5, NOTE_C5, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_A4,
  NOTE_AS4, NOTE_AS4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_AS4, NOTE_AS4,
  NOTE_C5, NOTE_C5, NOTE_DS5, NOTE_DS5, NOTE_D5, NOTE_D5, NOTE_A4, NOTE_A4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, NOTE_F4, NOTE_F4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, NOTE_C4, NOTE_C4,
  NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_DS5, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_A4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, NOTE_F4, NOTE_F4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, NOTE_D4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.
float noteDurations[] = { 
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16,
  16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16, 16 / 3.0, 16
};


int win() {
  for (int thisNote = 0; thisNote < (sizeof(notes) / sizeof(int)); thisNote++) {
    float noteDuration = 2000 / noteDurations[thisNote];
    float pauseBetweenNotes = noteDuration * 1.30;
    tone(BUZZER, notes[thisNote], noteDuration);
    delay(pauseBetweenNotes);
  }
  while(1) {
    delay(1000);
  }
}


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  win();
}
