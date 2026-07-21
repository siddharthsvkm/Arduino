int voltPin = A4;
int buzzPin = 9;

int lowestLight = 10;
int highestLight = 450;
int highestBuzz = 1100;
int lowestBuzz = 40;
int tenBitNum = 0;
float delayTime = 0;


void setup() {
  pinMode(voltPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tenBitNum = analogRead(voltPin);
  delayTime = ((highestBuzz-lowestBuzz)/(highestLight-lowestLight)) * (tenBitNum-lowestLight) + lowestBuzz;

  Serial.print("Voltage is ");
  Serial.print(tenBitNum);
  Serial.print(" and Current Delay is ");
  Serial.println(delayTime);

  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(delayTime);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(delayTime);
}
