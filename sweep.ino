#include <Servo.h>

Servo servo1;

const int inPin = 2;
const int servoPin = 9;

int state = 1;
int readState;
int pos = 0;
int delayCounter = 0;
int increment = 1;
int delayTime = 12000;

long time = 0;
long deBoucne = 500;

void setup() {
  pinMode(inPin, INPUT);
  servo1.attach(servoPin);
  Serial.begin(9600);
  servo1.write(0);
}

int toggleState() {
  if (state == 1) {
    state = 0;
  } else {
    state = 1;
  }
  time = millis();
}

void runMotor() {
  if (state == 0) {
    if (pos >= 40) {
      increment = -1;
    } else if (pos <= 0) {
      increment = 1;
    }
    pos += increment;
    servo.write(pos);
  }
}

void loop() {
  readState = digitalRead(inPin);
  delayCounter += 1;
  
  if (readState == 0 && millis() - time > deBounce) {
    toggleState();
  }
  
  if (delayCounter >= delayTime) {
    delayCounter = 0;
    runMotor();
  }
}
