#include <Servo.h>

int servoPin = 7;
int joystickXPin = A1;
int joystickYPin = A0;
int delayTime = 50;
Servo myServo;
int position = 0;

void setup() {
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int xPos = analogRead(joystickXPin);
  int yPos = analogRead(joystickYPin);

  if (position == 180 ) {
    if (xPos > 512 )  {
      position -=1;
    } if (yPos < 512) {
      position -=1;
    }
  } else if (position > 0 ) {
      if (xPos > 512 )  {
        position -=1;
      } if (xPos < 512) {
        position +=1;
      } if (yPos > 512) {
        position +=1;
      } if (yPos < 512) {
        position -=1;
      }
  } else if (position == 0) {
      if (xPos < 512) {
        position +=1;
      } if (yPos > 512) {
        position +=1;
      }
  } 
  
  String statement = String(xPos) + " " + String(yPos) + " " + String(position);
  Serial.println(statement);
  myServo.write(position);
  delay(50);
}
