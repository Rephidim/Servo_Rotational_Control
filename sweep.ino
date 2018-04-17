/*
* Automated Flashpoint Restricted-Angle Oscillator software
* Marty PoVey
*/
#include <VarSpeedServo.h>

VarSpeedServo servo;


const int inPin = 2;
const int angleL = 40;
const int angleR = 0;
const int spd = 10;

int state = LOW;
int readState;
int previousState = LOW;

long time = 0;
long deBounce = 200;

void setup() {
  pinMode(inPin, INPUT);
  servo.attach(9);
}

void loop() {
  
  readState = digitalRead(inPin);

  if (readState == HIGH && previousState == LOW && millis() - time > deBounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
  }

  if (state == HIGH) {
    servo.write(angleL, spd, true);
    servo.write(angleR,spd,true);
  }
  
  previousState = readState;
}
