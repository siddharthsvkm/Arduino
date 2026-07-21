int readPin = A2;
int lightPin = 3;

int delayTime = 250;
float voltage = 0;
int tenbitNumber = 0;

void setup() {
  pinMode(lightPin, OUTPUT);
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  tenbitNumber = analogRead(readPin);
  voltage = (5.0/1023.0) * tenbitNumber;
  if (voltage > 4) {
    Serial.print("The voltage is too high: ");
    digitalWrite(lightPin, HIGH);
  }
  if (voltage <= 4) {
    Serial.print("The voltage is enough: ");
    digitalWrite(lightPin, LOW);
  }
  
  Serial.println(voltage);
  delay(delayTime);
}
