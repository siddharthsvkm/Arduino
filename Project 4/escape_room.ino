#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Servo myServo;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
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



int servoPin = 7;
int buzzerPin = 6;
int photoresistor = A7;
int buttonPressed[] = {24, 25, 30, 31};
int leds[] = {26, 27, 28, 29, 34, 36};

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
  for (int led = 0; led < 6; led++) {
    pinMode(leds[led], OUTPUT);
  }

  randomSeed(analogRead(A1));
  lcd.begin(16,2);
  myServo.attach(servoPin);
  myServo.write(90);
  printLCD("Escape Room", "Puzzle Simulator");
}

void loop() {
  if (!p1Status) {
    puzzle1(&p1Status, leds, buttonPressed);
  }
  // puzzle2(p2Status);
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
  delay(6000);
}

// void completedRoom(int roomStatus, bool ledStatus) {
//   int leds[] = {36, 34};
//   if (ledStatus) {
//     analogWrite(leds[roomStatus], 255);
//   } else {
//     analogWrite(leds[roomStatus], 0);
//   }
// }

void puzzle1(bool* p1Status, int* ledNum, int* buttonPressed) {
  myServo.write(180);
  printLCD("Puzzle 1 -", "Memory Test");
  printLCD("Follow the", "lights");

  int patternNum = 6;
  int recordedPattern[patternNum];
  byte randomNum;
  for (int count = 0; count < patternNum; count++) {
      randomNum = random() % 4;
      if (count > 0 && randomNum == recordedPattern[count - 1]) {
        randomNum = (randomNum + count) % 4;
      }
      recordedPattern[count] = randomNum % 4;
      digitalWrite(ledNum[randomNum], HIGH);
      delay(600);
      digitalWrite(ledNum[randomNum], LOW);
      delay(600);
  }

  int count = 0;
  int button;
  int pressedCount;
  printLCD("Turn on the", "lights");
  while (count < patternNum) {
    button = -1;
    pressedCount = 0;

    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPressed[i]) == HIGH) {
          button = i;
          pressedCount += 1;
      }
    }
    if (pressedCount > 1) {
      break;
    } else if (button == recordedPattern[count]) {
      while (digitalRead(buttonPressed[button]) == HIGH) {
        digitalWrite(ledNum[button], HIGH);
      } 
      digitalWrite(ledNum[button], LOW);
      delay(20);
      count += 1;
    } else if (button == -1) {
      delay(15);
      continue;
    } else {
      break;
    }

  }
  if(count == patternNum) {
    *p1Status = true;
    myServo.write(0);
    printLCD("Completed Room1-", "Memory Test");
  } else {
    tryAgain(1);
  }
}

void puzzle2(bool* p1Status) {
  myServo.write(180);
  printLCD("Puzzle 2 -", "Light Test");
  printLCD("Room must", "become dark");

  int brightness;
  while (brightness > 50) {
    
  }

}


// void puzzle3(int p3Status) {
  
// }
// void puzzle4(int p4Status) {
  
// }
// void puzzle5(int p5Status) {
  
// }
