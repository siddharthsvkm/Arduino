// Siddharth Sivakumar
// July 22, 2026
// Arduino Mega
/* The purpose of this program is to use a joystick 
to control the current position within a 1023x1023 
plane and output to an LCD display (LCD1602 Module). 
The joystick can be pressed to release a warning sound. */

#include <LiquidCrystal.h>
int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int switchPin = 7;
int xPosPin = A8;
int yPosPin = A9;
int buzzerPin = 6;

String outputString;
int xPos;
int yPos;
int switchButton;
int delayTime = 250;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(xPosPin, INPUT);
  pinMode(yPosPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(switchPin, HIGH);

  lcd.begin(16, 2);
}

void loop() {
  xPos = analogRead(xPosPin);
  yPos = analogRead(yPosPin);
  switchButton = digitalRead(switchPin);

  outputString = "(x,y): "+ String(xPos) + "," + String(yPos);
  Serial.println(outputString);
  lcd.print(outputString);

  lcd.setCursor(0, 1);
  if (switchButton == 0) {
    lcd.print("ON");
    digitalWrite(buzzerPin, HIGH);
  } else {
    lcd.print("OFF");
    digitalWrite(buzzerPin, LOW);
  }
  delay(delayTime);
  lcd.clear();
}
