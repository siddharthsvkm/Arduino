int redPin = 13;
int greenPin = 12;
int bluePin = 11;



void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  int redVal = (255 / 1023.0) * analogRead(A0);
  int blueVal = (255 / 1023.0) * analogRead(A2);
  int greenVal = (255 / 1023.0) * analogRead(A1);
  digitalWrite(redPin, redVal);
  digitalWrite(greenPin, greenVal);
  digitalWrite(bluePin, blueVal);
  String statement = "Red: " + String(redVal) + " Green: " + String(greenVal) + " Blue: " + String(blueVal);
  Serial.println(statement);

  delay(200);
}
