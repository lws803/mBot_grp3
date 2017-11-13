#include "MeOrion.h"
#include "PID_v1.h"
#include "notes.h"
#define BUZZER 8
#define IR_SIDE_L A1
#define IR_SIDE_R A0
#define IR_DOWN_L 11
#define IR_DOWN_R 12
#define TIMEOUT 30000
#define SOUND A3
#define LIGHT A6


// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

int count = 0;
double outputL, outputR, inputL, inputR, setpointL, setpointR, win = 0; 

double aggKp_l=2.5, aggKi_l=0, aggKd_l=1;

double consKp_l=1, consKi_l=0.2, consKd_l=0;

double aggKp_r=3.5, aggKi_r=0, aggKd_r=1;

double consKp_r=1, consKi_r=0.2, consKd_r=0;

PID myPID_L(&inputL, &outputL, &setpointL,consKp_l,consKi_l,consKd_l, DIRECT); 
PID myPID_R(&inputR, &outputR, &setpointR,consKp_r,consKi_r,consKd_r, DIRECT);

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


int win_play() {
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


void left() {
  motorL.run(130);
  motorR.run(130);
  delay(540);
}
void right() {
  motorL.run(-130);
  motorR.run(-130);
  delay(540);
}

void go(int seconds) {
  motorL.run(-130);
  motorR.run(130);
  delay(seconds);
}
void reverse() {
  motorL.run(130);
  motorR.run(-130);
  delay(200);
}
void wait() {
  motorL.stop();
  motorR.stop();
  //delay (1000);
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

int soundChallenge() {
  // 
  double average = 0, v;
  for (int i = 0; i < 10; i++) {
    average += (double)analogRead(SOUND) / 1023.0 * 5.0;
    delay(100);
  }
  
  v = average/10;
  
  if(v >= 0.0 && v < 1.0) return 0;
  else if(v >= 1.0 && v < 2.3) { right(); }
  else if(v >= 2.3 && v < 5.0) { left(); }
  return 1;
}

int lightChallenge() {
  double v = (double)analogRead(LIGHT) / 1023.0 * 5.0;
  Serial.print("Light sensor voltage reading: ");
  Serial.println(v);
  if(v >= 0.0 && v < 1.3) return 0;
  else if(v >= 1.3 && v < 2.6) { right(); }
  else if(v >= 2.6 && v < 3.9) { left(); }
  //else if(v >= 3.9 && v < 5.0) { }
  return 1;
}


void setup() {
  inputL = analogRead(IR_SIDE_L);
  inputR = analogRead (IR_SIDE_R);

  myPID_L.SetMode(AUTOMATIC);
  myPID_R.SetMode(AUTOMATIC);
  
  double left_sum = 0, right_sum = 0;
  delay(1000);
  for (int i = 0; i < 10; i++) {
    left_sum += inputL;
    right_sum += inputR;
    delay (100);
  }
  setpointL = left_sum/10;
  setpointR = right_sum/10;

  Serial.begin (9600);

}

void loop() {
    inputL = analogRead(IR_SIDE_L)  ;
    inputR = analogRead (IR_SIDE_R) ;

    int f = blackLine();
    
    double gap_l = abs(setpointL-inputL); //distance away from setpoint
    if(gap_l<10)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID_L.SetTunings(consKp_l, consKi_l, consKd_l);
    }
    else
    {
     //we're far from setpoint, use aggressive tuning parameters
      myPID_L.SetTunings(aggKp_l, aggKi_l, aggKd_l);
    }

    double gap_r = abs(setpointR-inputR); //distance away from setpoint
    if(gap_r<10)
    {  //we're close to setpoint, use conservative tuning parameters
      myPID_R.SetTunings(consKp_r, consKi_r, consKd_r);
    }
    else
    {
     //we're far from setpoint, use aggressive tuning parameters
      myPID_R.SetTunings(aggKp_r, aggKi_r, aggKd_r);
    }

    if (f) {
      wait();
      if(!soundChallenge() && !lightChallenge()) {
        win = 1;
        win_play();
        motorL.run(0);
        motorR.run(0);
      }
      go(1000);
    }
    else if (!win){
      myPID_L.Compute();
      myPID_R.Compute();
      motorL.run(-(140 + outputL/2));
      motorR.run(140 + outputR/2);
    }    
}
