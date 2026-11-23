#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <RTClib.h>

RTC_DS1307 myRTC;

Servo myServo;
int servoPin = 23;

int rs = 13, e = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal myLCD(rs, e, d4, d5, d6, d7);

const int row = 4, col = 4;
char safeKeys[row][col] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
uint8_t colPins[col] = {47, 49, 51, 53};
uint8_t rowPins[row] = {39, 41, 43, 45};
Keypad safeKeypad = Keypad(makeKeymap(safeKeys), rowPins, colPins, row, col);


int colorPins[] = {5, 6, 7};
int numColors = sizeof(colorPins) / sizeof(colorPins[0]);

bool lockStatus;
char pinCode[4];
bool startMenu = false;
bool repeatText = true;


void setup() {
  for (int num = 0; num < numColors; num++) {
    pinMode(colorPins[num], OUTPUT);
  }
  if (!myRTC.begin()) {
    printLCD("RTC not found", "Check wiring", 10000);
  }
  myServo.attach(servoPin);
  myServo.write(90);
  myLCD.begin(16,2);
  printLCD("Digital SafeLock", "Simulator", 1000);

  while (true) {
    if (enterPin(true, true)) {
      touchSafe(true);
      break;
    }
  }
}

void loop() {
  menu();
  delay(30);
}

void menu() {
  if (!startMenu && repeatText) {
    printLCD("SafeLock Menu", "Press '#' option", 100);
    repeatText = false;
  }

  char continueMenu = safeKeypad.getKey();
  if (continueMenu == '#') {
    repeatText = true;
    startMenu = false;
    if (lockStatus) {
      printLCD("A-Unlock|B-Back", "C-Change|D-Date", 10);
    } else {
      printLCD("*-Lock|B-Back", "C-Change|D-Date", 10);
    }
    char input;
    while (true) {
      input = safeKeypad.getKey();
      
      if (input == '*' && !lockStatus) { // Lock the safe
        touchSafe(true);
        return;

      } else if (input == 'A' && lockStatus) { // Open the safe
        if (enterPin(false, true)) {
          touchSafe(false);
          return;
        } else {
          return;
        }
      } else if (input == 'B') {
        return;

      } else if (input == 'C' && enterPin(false, false)) {
        enterPin(true, true);
        touchSafe(true);
        printLCD("Changed Password", "     [****]", 1000);
        return;

      } else if (input == 'D') {
        printDate();
        return;
      }
    }
  }
}

bool enterPin(bool reset, bool required) {
  bool unlock = true;
  int counter = 0, incorrect = 0;
  char input;
  String pinInterface;

  if (reset) {
    printLCD("Set 4-Digit PIN", "     [____]", 10);
  } else {
    counter += 4;
    printLCD("Confirm Lock PIN", "     [____]", 10);
  }
  
  while (counter < 8) {
    input = safeKeypad.getKey();
    if (input >= '0' && input <= '9') {
      if (counter < 4) {
        pinCode[counter] = input;
      } else if (counter >= 4 && input != pinCode[counter - 4]) {
        incorrect += 1;
        unlock = incorrectAttempt(&incorrect);
        if (!unlock) {
          return false;
        }
        printLCD("Confirm Lock PIN", "     [____]", 200);
        myLCD.setCursor(0,1);
        counter = 4;
        continue;
      }
      counter += 1;
      printPINInterface(counter);
      if (counter == 4) {
        delay(200);
        printLCD("Confirm Lock PIN", "     [____]", 200);
      }
    } else if (input == 'B' && !required) {
        return false;
    } else if (input == 'B' && reset) {
      counter = 0;
      printLCD("Set 4-Digit PIN", "     [____]", 200);
    }
    delay(30);
  }
  if (counter == 8) {
    return true;
  }
}

void printPINInterface(int count) {
  myLCD.setCursor(0,1);
  myLCD.print("     [");
  for (int pinNums = 0; pinNums < 4; pinNums++) {
    if (count % 4 > 0) {
      myLCD.print("*");
      count -= 1;
    } else {
      myLCD.print("_");
    }
  }
  myLCD.print("]");
}


bool incorrectAttempt(int* incorrect) {
  int left = *incorrect;
  if (left == 3) {
    printLCD("Incorrect PIN", "5 Sec Lockout", 5000);
    printLCD("Navigating back", "to start menu", 3000);
    return false;
  } else {
    printLCD("Incorrect PIN", String(3 - left) + " Attempts Left", 2000);
    return true;
  }
}

void printDate() {
  int prevSec = -1;
  DateTime myClock;
  char input = safeKeypad.getKey();
  char dateStatement[17];
  char timeStatement[17];

  while (input != 'B') {
    input = safeKeypad.getKey();
    myClock = myRTC.now();
    
    if (myClock.second() != prevSec){
      snprintf(dateStatement, sizeof(dateStatement), "Date %02d/%02d/%02d", myClock.month(), myClock.day(), myClock.year());
      snprintf(timeStatement, sizeof(timeStatement), "Time %02d:%02d:%02d", myClock.hour(), myClock.minute(), myClock.second());
    
      myLCD.setCursor(0, 0);
      myLCD.print(dateStatement);
      myLCD.print("   ");

      myLCD.setCursor(0, 1);
      myLCD.print(timeStatement);
      myLCD.print("   ");

      prevSec = myClock.second();
    }

    delay(45);
  }
}

// Press '*'
void touchSafe(bool lock) {
  if (lock) {
    lockStatus = true;
    myServo.write(180);
    safeColor('r');
    printLCD("Locked Safe", "", 1000);
  } else {
    lockStatus = false;
    myServo.write(0);
    safeColor('g');
    printLCD("Unlocked Safe", "", 1000);
  }
}


void safeColor(char color) {
  int red = 7, green = 6, blue = 5;
  if (color == 'r') {
    analogWrite(red, 255);
    analogWrite(green, 0);
    analogWrite(blue, 0);
  } else if (color == 'g') {
    analogWrite(red, 0);
    analogWrite(green, 255);
    analogWrite(blue, 0);
  } else if (color == 'n') {
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
  } 
}


void printLCD(String statement1, String statement2, int delayTime) {
  myLCD.clear();
  myLCD.setCursor(0,0);
  myLCD.print(statement1);
  myLCD.setCursor(0,1);
  myLCD.print(statement2);
  delay(delayTime);
}
//     }
// }
