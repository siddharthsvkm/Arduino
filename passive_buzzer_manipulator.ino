int buzzPin = 9;
int analogPin = A9;

float finalDelay = 0;
int tenBitNum = 0;

int delayTimeHigh = 1000;
int delayTimeLow = 60;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzPin, OUTPUT);
  pinMode(analogPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  tenBitNum = analogRead(analogPin);

  finalDelay = ((delayTimeHigh-delayTimeLow)/(1023.0)) * tenBitNum + delayTimeLow;

  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(finalDelay);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(finalDelay);
  Serial.print("The delay is ");
  Serial.print(finalDelay);
  Serial.println(" microseconds.");
}


