// Siddharth Sivakumar
// July 1, 2026
// Arduino MEGA
// The purpose of this program

int buzzerPin = 9; // Can be modified or changed to match current pin of Arduino
int analogPin = A9; // Can be modified or changed to match current pin of Arduino

float finalDelay = 0;
int tenBitNum = 0;

int delayTimeHigh = 1000;
int delayTimeLow = 60;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  tenBitNum = analogRead(analogPin);
  finalDelay = ((delayTimeHigh-delayTimeLow)/(1023.0)) * tenBitNum + delayTimeLow;

  digitalWrite(buzzerPin, HIGH);
  delayMicroseconds(finalDelay);
  digitalWrite(buzzerPin, LOW);
  delayMicroseconds(finalDelay);
  Serial.print("The delay is ");
  Serial.print(finalDelay);
  Serial.println(" microseconds.");
}
