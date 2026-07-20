int redLight = 4;
int greenLight = 3;
int blueLight = 2;
int delayTime = 700;

void setup() {
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(blueLight, OUTPUT);

}

void loop() {
  digitalWrite(redLight, HIGH);
  delay(delayTime);
  digitalWrite(greenLight, HIGH);
  delay(delayTime);
  digitalWrite(blueLight, HIGH);
  delay(delayTime);
  digitalWrite(greenLight, LOW);
  delay(delayTime);
  digitalWrite(redLight, LOW);
  delay(delayTime);
  digitalWrite(greenLight, HIGH);
  delay(delayTime);
  digitalWrite(greenLight, LOW);
  delay(delayTime);
  digitalWrite(blueLight, LOW);
}
