int switchPin = 9;
int xPosPin = A8;
int yPosPin = A9;
int buzzPin = 3;

int xPos;
int yPos;
int switchButton;
int delayTime = 1500;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(xPosPin, INPUT);
  pinMode(yPosPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(switchPin, HIGH);
}

void loop() {
  xPos = analogRead(xPosPin);
  yPos = analogRead(yPosPin);
  switchButton = digitalRead(switchPin);

  Serial.print("(x,y): ");
  Serial.print(xPos);
  Serial.print(", ");
  Serial.print(yPos);

  Serial.print(" - ");
  Serial.print(switchButton);
  if (switchButton == 0) {
    Serial.println(" on");
    digitalWrite(buzzPin, HIGH);
  } else {
    Serial.println(" off");
    digitalWrite(buzzPin, LOW);
  }
}
