// Siddharth Sivakumar
// July 20, 2026
// Arduino Mega
/* This is my first program using the rotary encoder module/joystick. 
The purpose of this program is to use a joystick 
to control the current position within a 1023x1023 plane. 
The joystick can be pressed to release a warning sound. */

int switchPin = 9; // Input pin for the joystick switch
int xPosPin = A8; // Input pin for the x-coordinate from the joystick - uses a potentiometer
int yPosPin = A9; // Input pin for the y-coordinate from the joystick - uses a potentiometer
int buzzerPin = 3; // Output pin to create the warning buzz when the joystick is pressed

int xPos; // X-coordinate variable
int yPos; // Y-coordinate variable
int switchButton; // Switch variable that checks whether the joystick is pressed
int delayTime = 250; // Delay variable that slows down the reading of input

void setup() {
  // Set up input and output pins on the Arduino board
  pinMode(switchPin, INPUT);
  pinMode(xPosPin, INPUT);
  pinMode(yPosPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  // Set up serial port to print to the Serial Monitor on the Arduino IDE
  Serial.begin(9600);
  // Activate switch on the joystick
  digitalWrite(switchPin, HIGH);
}

void loop() {
  // Read from the input pins and store in the declared variables
  xPos = analogRead(xPosPin);
  yPos = analogRead(yPosPin);
  switchButton = digitalRead(switchPin);

  // Print xy coordinates to Serial Monitor to visually see
  Serial.print("(x,y): ");
  Serial.print(xPos);
  Serial.print(", ");
  Serial.print(yPos);

  // Print the condition of the switch - on or off
  Serial.print(" - ");
  if (switchButton == 0) {
    Serial.println(" on");
    digitalWrite(buzzerPin, HIGH);
  } else {
    Serial.println(" off");
    digitalWrite(buzzerPin, LOW);
  // Create a delay so the user can comfortably see the output
  delay(delayTime);
}
