#include <Servo.h>
Servo myServo;

int analogPin = A9;
int servoPin = 9;

int lowestPos = 0;
int highestPos = 175;
int highestLight = 400;
int lowestLight = 0;
float currentPos;
int currentLight;
int delayTime = 500;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  currentLight = analogRead(analogPin);
  currentPos = 1.0 * currentLight / (highestLight - lowestLight) * (highestPos - lowestPos);
  
  myServo.write(currentPos);
  Serial.print("Position of the Servo: ");
  Serial.println(currentPos);
  delay(delayTime);
}
