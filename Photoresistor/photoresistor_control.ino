int redLight = 9;
int greenPin = 6;
int voltagePin = A9;

int tenBitNum = 0;
int delayTime = 350;

void setup() {
  pinMode(redLight, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(voltagePin, INPUT);
  Serial.begin(9600);
}

void loop() {
  tenBitNum = analogRead(voltagePin);

  Serial.print("The light is ");
  if (tenBitNum <= 220) {
    Serial.print("off: ");
    digitalWrite(redLight, HIGH);
    digitalWrite(greenPin, LOW)
  } else {
    Serial.print("on: ");
    digitalWrite(greenPin, HIGH);
    digitalWrite(redLight, LOW);
  }
  Serial.println(tenBitNum);
  delay(delayTime);
}
