#include "MeOrion.h"
#define TIMEOUT 30000
#define ULTRASONIC_SENSOR_PIN 12

MeDCMotor motorL(M1);
MeDCMotor motorR(M2);
uint8_t motorSpeedL = 100;
uint8_t motorSpeedR = 100;

//move forward with echolocation to avoid crashing
void echolocation() {
  long duration;
  double distance;
  motorL.run(-motorSpeedL);
  motorR.run(motorSpeedR);
  while(1) {
    pinMode(ULTRASONIC_SENSOR_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_SENSOR_PIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
  
    pinMode(ULTRASONIC_SENSOR_PIN, INPUT);
    duration = pulseIn(ULTRASONIC_SENSOR_PIN, HIGH, TIMEOUT);
    distance = duration / 2.0 * 0.034;
    //Serial.println(distance);
    if(distance < 10.0) {
      motorL.stop();
      motorR.stop();
      break;
    }
  }  
}

void setup() {
  //Serial.begin(9600);
}

void loop() {
  echolocation();
  delay(5000);
}
