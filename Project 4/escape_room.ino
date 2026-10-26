// import libraries for external components and modules
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// set up servo and lcd display
Servo myServo;
int servoPin = 7;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// set up each row and column of keypad
const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
uint8_t colPins[COLS] = {41, 43, 45, 47};
uint8_t rowPins[ROWS] = {40, 42, 44, 46};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);




int buzzerPin = 6;
int buttonPressed[] = {24, 25, 30, 31};
int leds[] = {26, 27, 28, 29};

bool p1Status = false;
bool p2Status = false;
bool p3Status = false;
bool p4Status = false;
bool p5Status = false;

// void puzzle1(bool);
// void puzzle2(bool);
// void puzzle3(bool);
// void puzzle4(bool);
// void puzzle5(bool);

void setup() {
  for (int pressed = 0; pressed < 4; pressed++) {
    pinMode(buttonPressed[pressed], INPUT);
  }
  for (int led = 0; led < 4; led++) {
    pinMode(leds[led], OUTPUT);
  }

  randomSeed(analogRead(A1));
  lcd.begin(16,2);
  myServo.attach(servoPin);
  myServo.write(90);
  printLCD("Escape Room", "Puzzle Simulator");
}

void loop() {
  lightsOff(leds);
  if (!p1Status) {
    puzzle1(&p1Status, leds, buttonPressed);
  }
  else if (!p2Status) {
    puzzle2(&p2Status, leds, buttonPressed);
  }
  // puzzle3(p3Status);
  // puzzle4(p4Status);
  // puzzle5(p5Status);
}

void tryAgain(int puzzleNum) {
  String statement = "Puzzle " + String(puzzleNum) + ": Failed";
  printLCD(statement, "Please try again");
}

void printLCD(String statement1, String statement2) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(statement1);
  lcd.setCursor(0,1);
  lcd.print(statement2);
  delay(3000);
}

// void completedRoom(int roomStatus, bool ledStatus) {
//   int leds[] = {36, 34};
//   if (ledStatus) {
//     analogWrite(leds[roomStatus], 255);
//   } else {
//     analogWrite(leds[roomStatus], 0);
//   }
// }

void lightsOff(int* ledPins) {
  digitalWrite(ledPins[0], LOW);
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[3], LOW);
}

int buttonPress(int* buttons, int* ledPins, int mode) {
  int button = -1;
  while (true) {
    for (int count = 0; count < 4; count++) {
      if (digitalRead(buttonPressed[count]) == HIGH && mode == 1) {
        button = count;
        digitalWrite(ledPins[button], HIGH);
        while (digitalRead(buttonPressed[count]) == HIGH) {
          delay(10);
        }
        digitalWrite(ledPins[button], LOW);
        delay(20);
        return button;
    } else if (digitalRead(buttonPressed[count]) == HIGH && mode == 2) {
        button = count;
        digitalWrite(ledPins[button], HIGH);
        while (digitalRead(buttonPressed[count]) == HIGH) {
          delay(10);
        }
        delay(20);
        return button;
    }

    delay(20);
  }
}
}

void puzzle1(bool* p1Status, int* ledNum, int* buttonPressed) {
  myServo.write(180);
  printLCD("Puzzle 1 -", "Memory Test");
  printLCD("Task - Follow", "the lights");

  int sequenceLen = 6;
  int recordedPattern[sequenceLen];

  // generate the button numbers to use
  for (int count = 0; count < sequenceLen; count++) {
    if (count < 4) {
      recordedPattern[count] = count;
    }
    else {
      recordedPattern[count] = random() % 4;
    }
  }
  
  // shuffles the button numbers to create random order
  for (int count = sequenceLen - 1; count > 0; count--) {
    int randomIndex = random() % (count + 1);

    int temp = recordedPattern[count];
    recordedPattern[count] = recordedPattern[randomIndex];
    recordedPattern[randomIndex] = temp;
  }

  // show pattern to user through lights
  for (int count = 0; count < sequenceLen; count++) {
    int lightNum = recordedPattern[count];
    digitalWrite(ledNum[lightNum], HIGH);
    delay(800);
    digitalWrite(ledNum[lightNum], LOW);
    delay(800);
  }

  int count = 0;
  int button;
  int pressedCount;
  printLCD("Repeat the", "light sequence");
  int wrong = 0;

  for (int count = 0; count < sequenceLen; count++) {
    if (recordedPattern[count] != buttonPress(buttonPressed, ledNum, 1)) {
      tryAgain(1);
      return;
    }
  }
  *p1Status = true;
  myServo.write(0);
  printLCD("Room 1 Complete-", "Memory Test");

}

void puzzle2(bool* p2Status, int* ledNum, int* buttonPressed) {
  myServo.write(180);
  printLCD("Puzzle 2 -", "Einstein Logic");
  
  printLCD("Order the", "colored buttons");
  printLCD("according to", "this saying");

  printLCD("Red is certainly", "not first.");
  printLCD("Blue is close", "behind green.");
  printLCD("Yellow is far", "from red.");

  printLCD("Press the", "buttons in order");

  int pattern[] = {3, 1, 2, 0};

  for (int count = 0; count < 4; count++) {
    if (pattern[count] != buttonPress(buttonPressed, ledNum, 2)) {
      tryAgain(2);
      return;
    }
  }

  *p2Status = true;
  myServo.write(0);
  printLCD("Room 2 Complete-", "Einstein Logic");
}


void puzzle3(bool* p3Status, int* ledNum, int* buttonPressed) {
  
}
// void puzzle4(int p4Status) {
  
// }
// void puzzle5(int p5Status) {
  
// }
