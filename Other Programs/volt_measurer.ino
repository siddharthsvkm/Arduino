int voltagePin = A2;
int redPin = 9;
int yellowPin = 2;
int greenPin = 5;

float voltage = 0;
int volt10bit = 0;
int delayTime = 500;

void setup() {
  pinMode(voltagePin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  volt10bit = analogRead(voltagePin);
  voltage = (5.0/1023.0) * volt10bit;
  if (voltage<=3) {
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    
    Serial.print("The voltage is LOW: ");
  } else if (voltage<=4) {
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
    
    Serial.print("The voltage is MODERATE: ");
  } else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    
    Serial.print("The voltage is HIGH: ");
  }

  Serial.println(voltage);
  delay(delayTime);
}
