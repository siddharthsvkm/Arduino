int redPin = 13;
int bluePin = 11;
int greenPin = 9;
int yellowPin = 8;
int delayTime = 200;
int betweenNumber = delayTime * 5;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop() {
  redLight(redPin, betweenNumber);

  blueLight(bluePin, betweenNumber);

  blueLight(bluePin, delayTime);
  redLight(redPin, betweenNumber);

  greenLight(greenPin, betweenNumber);

  greenLight(greenPin, delayTime);
  redLight(redPin, betweenNumber);

  greenLight(greenPin, delayTime);
  blueLight(bluePin, betweenNumber);

  greenLight(greenPin, delayTime);
  blueLight(bluePin, delayTime);
  redLight(redPin, betweenNumber);
  
  yellowLight(yellowPin, betweenNumber);

  yellowLight(yellowPin, delayTime);
  redLight(redPin, betweenNumber);

  yellowLight(yellowPin, delayTime);
  blueLight(bluePin, betweenNumber);

  yellowLight(yellowPin, delayTime);
  blueLight(bluePin, delayTime);
  redLight(redPin, betweenNumber);

  yellowLight(yellowPin, delayTime);
  greenLight(greenPin, betweenNumber);
  
  yellowLight(yellowPin, delayTime);
  greenLight(greenPin, delayTime);
  redLight(redPin, betweenNumber);

  yellowLight(yellowPin, delayTime);
  greenLight(greenPin, delayTime);
  blueLight(bluePin, betweenNumber);

  yellowLight(yellowPin, delayTime);
  greenLight(greenPin, delayTime);
  blueLight(bluePin, delayTime);
  redLight(redPin, betweenNumber);
}

void redLight(int red, int betweenNumber) {
  digitalWrite(red, HIGH);
  delay(delayTime);
  digitalWrite(red, LOW);
  delay(betweenNumber);
}

void blueLight(int blue, int betweenNumber) {
  digitalWrite(blue, HIGH);
  delay(delayTime);
  digitalWrite(blue, LOW);
  delay(betweenNumber);
}

void greenLight(int green, int betweenNumber) {
  digitalWrite(green, HIGH);
  delay(delayTime);
  digitalWrite(green, LOW);
  delay(betweenNumber);
}

void yellowLight(int yellow, int betweenNumber) {
  digitalWrite(yellow, HIGH);
  delay(delayTime);
  digitalWrite(yellow, LOW);
  delay(betweenNumber);
}
