#include "MeOrion.h"
#define ULTRASONIC_SENSOR 10
#define TIMEOUT 30000
#define IR_SIDE_L A1
#define IR_SIDE_R A0

int count = 0, timer = 0;
double setpointL, setpointR;

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
  //Serial.print("\n\nDistance to the front wall: ");
  //Serial.println(distance);  
  return distance;  
}

double echolocation_2 () {
  double duration;
  double distance = 0;
  pinMode(ULTRASONIC_SENSOR, OUTPUT);
  digitalWrite(ULTRASONIC_SENSOR, LOW);
  if (timer == 0) {
    
  }

  if (timer >= 16) {
    digitalWrite(ULTRASONIC_SENSOR, HIGH);
  }

  if (timer == 32) {
    digitalWrite(ULTRASONIC_SENSOR, LOW);
    pinMode(ULTRASONIC_SENSOR, INPUT);
    duration = pulseIn(ULTRASONIC_SENSOR, HIGH, TIMEOUT);
    distance = duration / 2.0 * 0.034;
    timer = 0;  
  }
  
  timer++;
  
  //Serial.print("\n\nDistance to the front wall: ");
  //Serial.println(distance);  
  return distance; 
}

void setup() {
  double inputL = analogRead(IR_SIDE_L)  ;
  double inputR = analogRead(IR_SIDE_R)  ;
  
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
    double inputL = analogRead(IR_SIDE_L)  ;
    double inputR = analogRead(IR_SIDE_R)  ;
    int d = echolocation();
    // Filter 

    Serial.print (d);
    Serial.print (" ");
    // Distance control 
    if (d < 11) {
      count++;
    }else {
      count = 0;
    }

    // Cut off to turn, decrease the count to make it more responsive, add in IR sensor conditions here 
    // TODO: Measure difference between the two IR sensors and determine if it shd turn right or left. 
    double adjusted_L = inputL - setpointL; 
    double adjusted_R = inputR - setpointR;
    if (count > 50) {
      // Turn right 
      Serial.print (adjusted_L - adjusted_R);
    }
    Serial.println ("");

}
