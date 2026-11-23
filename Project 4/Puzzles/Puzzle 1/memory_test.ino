// import libraries for external components and modules
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int pressLED[] = {5, 4, 3, 2};

int level = 1;
int attempts = 0;
int newLevel = true;

const int sequenceLen = 6;
int recordedPattern[sequenceLen];


void setup() {
  randomSeed(analogRead(A1));
  lcd.begin(16,2);
}

void loop() {
  if (level < 10) {
    puzzle();
  } else {
    String statement = "- " + String(attempts) + " attempts";
    printLCD("Congratulations", statement, 5000);
    return;
  }
  delay(230);
}


void printLCD(String statement1, String statement2, int delayTime) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(statement1);
  lcd.setCursor(0,1);
  lcd.print(statement2);
  delay(delayTime);
}

int buttonPress() {
  int button = -1;
  while (true) {
    for (int count = 0; count < 4; count++) {
      if (digitalRead(pressLED[count]) == HIGH) {
        button = count;
        while (digitalRead(pressLED[count]) == HIGH) {
          delay(10);
        }
        delay(20);
        return button;
      }
    delay(20);
    }
  }
}

void puzzle() {
  attempts += 1;
  if (level == 1) {
    printLCD("Cognitive Puzzle", "- Memory Test", 5000);
    printLCD("Follow the", "light pattern", 4000);
  } else {
    printLCD("Follow the", "light pattern", 1000);
  }

  // Make GPIOs send output to light LEDS
  for (int x = 0; x < 4; x++) {
    pinMode(pressLED[x], OUTPUT);
  }
  if (newLevel) {
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
  }

  int lightTime = level * (-50) + 1000;
  // show pattern to user through lights
  for (int count = 0; count < sequenceLen; count++) {
    int lightNum = recordedPattern[count];
    digitalWrite(pressLED[lightNum], HIGH);
    delay(lightTime);
    digitalWrite(pressLED[lightNum], LOW);
    delay(lightTime + 20);
  }


  printLCD("Repeat the", "light sequence", 100);

  // Make GPIOs recieve input to track light pattern
  for (int x = 0; x < 4; x++) {
    pinMode(pressLED[x], INPUT);
  }

  for (int count = 0; count < sequenceLen; count++) {
    if (recordedPattern[count] != buttonPress()) {
      printLCD("Puzzle Failed", "Please try again", 3000);
      newLevel = false;
      return;
    }
  }
  String completeStatement = "Level " + String(level) + " Complete";
  printLCD(completeStatement, "- Memory Test", 3000);
  level += 1;
  newLevel = true;
}
