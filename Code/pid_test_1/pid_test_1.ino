#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
int ledPin = 13;


//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,1,0,0, DIRECT);
/*
 * Some observations: 
 * Setting Kd to 0 makes response in adjustment slower (LED slowly dims)
 * Leaving just Kp we will get proportional response as PID is now directly proportional to LED 
 * The rest will help in some form of predictive counter measures for adjusting the LED to keep Input above setPoint 
 */
void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = 100; // LED will turn on whenever LDR falls below 100

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop()
{
  Input = analogRead(0);
  int input_int = Input;
  int output_int = Output;
  myPID.Compute();
  analogWrite(ledPin, Output);
  analogWrite(3,Output);
  if (output_int > 0) {
    Serial.print ("Input: ");
    Serial.println(input_int);
    Serial.print ("Output: ");
    Serial.println (output_int);
  }
  delay (100);
}


