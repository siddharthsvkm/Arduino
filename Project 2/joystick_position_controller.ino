#include <LiquidCrystal.h>

int rs = 13, e = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

int joystickYPin = A1;
int joystickXPin = A0;
int greenPin = 22;
int purplePin = 23;
int bluePin = 24;
int redPin = 25;
int rgbPinR1 = 7;

int xPos;
int yPos;
String xDirectionList[] = {"Left", "Right", ""};
String yDirectionList[] = {"Down", "Up", ""};

void setup() {
  pinMode(bluePin, OUTPUT);
  pinMode(purplePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  for (int colorPin = 7; colorPin > 1; colorPin--) {
    pinMode(colorPin, OUTPUT);
  }

  lcd.begin(16, 2);
  lcd.print("JoystickPosition");
  lcd.setCursor(0,1);
  lcd.print("Controller");
  delay(6000);
}

void loop() {
  int xVal = analogRead(joystickXPin) - 512;
  int yVal = analogRead(joystickYPin) - 512;
  int multiplier = 2;
  xPos -= xVal * (multiplier * 10) / (512 * 10);
  yPos += yVal * (multiplier * 10) / (512 * 10);
  String positionStatement = "(x,y):(" + String(xPos) + "," + String(yPos) + ")";
  String xDirection = xDirectionList[(xVal < 0) + 2 * (xVal == 0)] ;
  String yDirection = yDirectionList[(yVal > 0) + 2 * (yVal == 0)];
  String directionMoving = "Moving " + xDirection  + yDirection;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(positionStatement);
  lcd.setCursor(0,1);
  lcd.print(directionMoving);
  colorDirections((xVal > 0) + 2 * (xVal == 0), (yVal < 0) + 2 * (yVal == 0));
  delay(150);
}

void colorDirections(int xDirection, int yDirection) {
  int blue = xDirection * (2 - xDirection);
  int red = 1 - ((xDirection + 1) / 2);
  int green = yDirection * (2 - yDirection);
  int purple = 1 - ((yDirection + 1) / 2);
  digitalWrite(bluePin, blue);
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(purplePin, purple);
  
  if (xDirection < 2 && yDirection < 2) {
    analogWrite(rgbPinR1, red * 255);
    analogWrite(rgbPinR1 - 1, green * 255);
    analogWrite(rgbPinR1 - 2, blue * 255);

    analogWrite(rgbPinR1 - 3, red * 255);
    analogWrite(rgbPinR1 - 4, green * 255);
    analogWrite(rgbPinR1 - 5, blue * 255);
    
    if (purple == 1) {
      analogWrite(rgbPinR1, (red * 255 + 170) / 2);
      analogWrite(rgbPinR1 - 2, (blue * 255 + 255) / 2);

      analogWrite(rgbPinR1 - 3, (red * 255 + 170) / 2);
      analogWrite(rgbPinR1 - 5, (blue * 255 + 255) / 2);
    }
  } else {
    analogWrite(rgbPinR1, 0);
    analogWrite(rgbPinR1 - 1, 0);
    analogWrite(rgbPinR1 - 2, 0);

    analogWrite(rgbPinR1 - 3, 0);
    analogWrite(rgbPinR1 - 4, 0);
    analogWrite(rgbPinR1 - 5, 0);
  }
}
