/**
* Code Refactored and Improved by Brian Blake
**/

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <Servo.h>

const int SERVO_PIN = 9;
const int RECEIVE_PIN = 11;

const int SIGNAL_DELAY = 10; //Without a pause between recieving a signal one button press can result in many signals
const long POWER = 0x00FFA25D; //The power button on our remote
const int PAUSE = 10; //The pause between swings
const int MAX_POS = 40;
const int MIN_POS = 0;

Servo servo1;
IRrecv irrecv(RECEIVE_PIN);

boolean on = 0;
unsigned long signalTime = SIGNAL_DELAY;
unsigned long time = millis();

int increment = 1;
int pause = PAUSE;
int srvoPos = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //Start the receiver
  irrecv.blink13(true); //Enable the LED
  servo1.attach(SERVO_PIN);
  servo1.write(0);
}

void loop(){
  //Pause between loops
  if(millis() + 40 > time) time += 40;
  else return;
  //Read in the signal
  decode_results results;
  if (irrecv.decode(&results)) irrecv.resume(); //Call resume if there was a signal
  if (++signalTime > SIGNAL_DELAY //If enough time has passed since the last signal
    && results.value == POWER){ //And if it was the right signal
    on ^= 1; //Toggle on
    signalTime = 0;
  }
  if (on) runMotor(); //Run the motor if on == true
}

void runMotor(){
  if (++pause < PAUSE) return; //Check if we are pausing
  if (srvoPos >= MAX_POS){ //Check to see if the servo is out of range
    pause = 0; //If so, pause
    increment = -1; //And reverse direction
  }
  if (srvoPos <= MIN_POS){ //ditto
    pause = 0;
    increment = 1;
  }
  servo1.write(srvoPos += increment); //Write the position to the servo
}
