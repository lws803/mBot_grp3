#include "MeOrion.h"
#include "PID_v1.h"
#include "notes.h"

// Sensor setups
#define BUZZER 8
#define LIGHT A6
#define SOUND A3
#define TIMEOUT 30000
#define ULTRASONIC_SENSOR 10
#define IR_DOWN_L 11
#define IR_DOWN_R 12
#define IR_SIDE_L A0
#define IR_SIDE_R A1
int emptyL, emptyR, soundReturn, lightReturn;

// Motor setups
MeDCMotor motorL(M1);
MeDCMotor motorR(M2);

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

// PID setups
double outputL, outputR, inputL,inputR, setpointL, setpointR;
PID myPID_L(&inputL, &outputL, &setpointL, 1, 1, 2, DIRECT); // Left PID
PID myPID_R(&inputR, &outputR, &setpointR, 1, 1, 2, DIRECT); // Right PID

// Raw driving functions
void wait() {
  motorL.stop();
  motorR.stop();
}
void go() {
  motorL.run(-255);
  motorR.run(255);
  delay(1000);
}
void left() {
  motorL.run(100);
  motorR.run(100);
  delay(750);
}
void right() {
  motorL.run(-100);
  motorR.run(-100);
  delay(750);
}

double echolocation() {
  double duration;
  double distance;  
  pinMode(ULTRASONIC_SENSOR, OUTPUT);
  digitalWrite(ULTRASONIC_SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR, HIGH);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_SENSOR, LOW);
  pinMode(ULTRASONIC_SENSOR, INPUT);
  duration = pulseIn(ULTRASONIC_SENSOR, HIGH, TIMEOUT);
  distance = duration / 2.0 * 0.034;  
  Serial.print("\n\nDistance to the front wall: ");
  Serial.println(distance);  
  return distance;  
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

// Functions for Challenges, 0 -> No, 1 -> Right, 2 -> Left, 3 -> Straight
int soundChallenge() {
  double v = (double)analogRead(SOUND) / 1023.0;
  if(v >= 0.0 && v < 1.0) return 0;
  if(v >= 1.0 && v < 2.3) return 1;
  if(v >= 2.3 && v < 5.0) return 2;
}
int lightChallenge() {
  double v = (double)analogRead(LIGHT) / 1023.0;
  if(v >= 0.0 && v < 1.3) return 0;
  if(v >= 1.3 && v < 2.6) return 1;
  if(v >= 2.6 && v < 3.9) return 2;
  if(v >= 3.9 && v < 5.0) return 3;
}
int win() {
  for (int thisNote = 0; thisNote < (sizeof(notes) / sizeof(int)); thisNote++) {
    float noteDuration = 2000 / noteDurations[thisNote];
    float pauseBetweenNotes = noteDuration * 1.3;
    tone(BUZZER, notes[thisNote], noteDuration);
    delay(pauseBetweenNotes);
  }
  wait();
  while(1) delay(1000);
}

void setup()
{
  // PID controls, above this value it will decrease rapidly
  setpointL = 600; // Left sensor
  setpointR = 450; // Right sensor
  // Turn the PID on
  myPID_L.SetMode(AUTOMATIC);
  myPID_R.SetMode(AUTOMATIC);

  // Turning controls, above this value it will recognize as clear path
  emptyL = 620;
  emptyR = 530;

  Serial.begin(9600);
}

void loop()
{
  //delay(1000);
  double d = echolocation();
  // Read voltage values across IR receivers
  inputL = analogRead(1); // Left - value gets lower when it gets closer
  inputR = analogRead(0); // Right - value gets lower when it gets closer  

  /*
  if(blackLine()) {
    wait();
    switch(soundChallenge()) {
      case 1: right(); go();
        break;
      case 2: left(); go();
        break;
      case 0: 
        switch(lightChallenge()) {
          case 1: right(); go();
            break;
          case 2: left(); go();
            break;
          case 3: go();
            break;
          case 0: win();
        }
    }    
  }

  else if(d < 10.0 && d) {
    if(inputL > emptyL && inputR <= emptyR) left(); // Only left side is empty
    if(inputR > emptyR && inputL <= emptyL) right(); // Only right side is empty
    // Else it is a failure of the ultrasonic sensor
  }

  else { */
    // Computation of PID outputs
    myPID_L.Compute();
    myPID_R.Compute();

    /**
    Serial.print("Leftward IR: ");
    Serial.print(inputL);
    Serial.print(", ");
    Serial.print(outputL);
    Serial.print("\tRight IR: ");
    Serial.print(inputR);
    Serial.print(", ");
    Serial.println(outputR);
    */

    Serial.print (inputL);
    Serial.print (" ");
    Serial.print (inputR);
    
    // Motor controls
    motorL.run(-(outputL + 100));
    motorR.run(outputR + 100);
  //}
}
