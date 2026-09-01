#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <RTClib.h>

RTC_DS1307 myRTC;
Servo myServo;
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

int servoPin = 23;
int buzzerPin = 2;

bool lockStatus;
char pinCode[4];
bool menuScreen = false;

void setup() {
  for (int color = 5; color <= 7; color++) {
    pinMode(color, OUTPUT);
  }
  myServo.attach(servoPin);
  myServo.write(90);
  myLCD.begin(16,2);
  printLCD("Digital SafeLock", "Simulator", 1000);
  enterPin(true, true);
}

void loop() {
  menu();
  delay(30);
}

void menu() {
  if (!menuScreen) {
    printLCD("SafeLock Menu", "Press '#' option", 100);
    menuScreen = true;
  }
  char continueMenu = safeKeypad.getKey();
  if (continueMenu == '#') {
    menuScreen = false;
    if (lockStatus) {
      printLCD("A-Unlock|B-Back", "C-Change|D-Date", 10);
    } else {
      printLCD("*-Lock|B-Back", "C-Change|D-Date", 10);
    }
    char input;
    while (true) {
      input = safeKeypad.getKey();
      // Lock the safe
      if (input == '*') {
        lockSafe(true);
        printLCD("Locked Safe", "", 10);
        break;
      }
      // Open the safe
      else if (input == 'A') {
        enterPin(false, true);
        break;
      } else if (input == 'B') {
        return;
      } else if (input == 'C') {
        enterPin(false, false);
        enterPin(true, true);
        printLCD("Changed Password", "     [****]", 1000);
        break;
      } else if (input == 'D') {
        printDate();
        break;
      }
    }
  }
}

void enterPin(bool reset, bool required) {
  bool unlock = true;
  int counter = 0, incorrect = 0;
  char input;
  String pinInterface;

  if (!reset) {
    counter += 4;
    printLCD("Confirm Lock PIN", "     [____]", 10);
  } else {
    printLCD("Set 4-Digit PIN", "     [____]", 10);
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
          break;
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
        unlock = false;
        break;
    } else if (input == 'B' && reset) {
      counter = 0;
      printLCD("Set 4-Digit PIN", "     [____]", 200);
    }
    delay(30);
  }
  if (!required && !reset) {

  } else if (unlock && !required) {
    lockSafe(false);
  } else {
    lockSafe(true);
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
  int left = *incorrect % 4;
  if (left == 3) {
    printLCD("Incorrect PIN", "10 Sec Lockout", 10000);
    printLCD("Navigate to open", "option again", 3000);
    return false;
  } else {
    printLCD("Incorrect PIN", String(3 - left) + " Attempts Left", 4000);
    return true;
  }
}

void printDate(){
  char input = safeKeypad.getKey();
  DateTime clock;
  while (input != 'B') {
    input = safeKeypad.getKey();
    clock = myRTC.now();
    int hour = clock.hour();
    int minute = clock.minute();
    int second = clock.second();

    String timeStatement = "Time ";
    if (hour <= 9 ){
      timeStatement += "0";
    }
    timeStatement += String(hour);
    timeStatement += ":";
    if (minute <= 9 ){
      timeStatement += "0";
    }
    timeStatement += String(minute);
    timeStatement += ":";
    if (second <= 9 ){
      timeStatement += "0";
    } 
    timeStatement += String(second);

    int day = clock.day();
    int month = clock.month();
    int year = clock.year();

    String dateStatement = "Date ";

    if (month <= 9 ){
      dateStatement += "0";
    }
    dateStatement += String(month);
    dateStatement += "/";
    
    if (day <= 9 ){
      dateStatement += "0";
    }
    dateStatement += String(day);
    
  
    dateStatement += "/";
    dateStatement += String(year);

    printLCD(dateStatement, timeStatement, 950);
  }  
}



void buzzerSound() {//int* status) {
  for (int count = 0; count < 4; count ++) {
      digitalWrite(buzzerPin, HIGH);
      tone(buzzerPin, 1050);
      delay(250);

      digitalWrite(buzzerPin, LOW);
      noTone(buzzerPin);
      delay(250);
    
    }
}

// Press '*'
void lockSafe(bool lock) {
  if (lock) {
    lockStatus = true;
    myServo.write(0);
    lockColor('r');
  } else {
    printLCD("Unlocked Safe", "", 10);
    lockStatus = false;
    myServo.write(180);
    lockColor('g');
  }
}


void lockColor(char color) {
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
