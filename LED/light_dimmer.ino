int voltagePin = A2;
int lightPin = 9;

int tenBitNumber = 0;
float brightness = 0;
int finalBrightness = 0;
int delayTime = 450;

void setup() {
  pinMode(voltagePin, INPUT);
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  tenBitNumber = analogRead(voltagePin);
  brightness = (tenBitNumber * 255.0) / 1023.0;
  finalBrightness = brightness;
  analogWrite(lightPin, finalBrightness);
  
  Serial.print("The brightness is ");
  Serial.println(finalBrightness);
  delay(delayTime);
}
