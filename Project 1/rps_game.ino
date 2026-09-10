#include <LiquidCrystal.h>

int switch1 = 13; // Red switch
int switch2 = 12; // Blue Switch
int switch3 = 11; // Green Switch

int lcd_rs = 7, lcd_e = 6, lcd_d4 = 5, lcd_d5 = 4, lcd_d6 = 3, lcd_d7 = 2;
LiquidCrystal lcd(lcd_rs, lcd_e, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

void setup() {
  lcd.begin(16,2);
  introduction();
}

void loop() {
  void playGame();
}

/*Rock, Paper, Scissors! Play Rock, 
Paper, or Scissors each round and try to outsmart 
your opponent, the computer. Good luck!*/
// Leftmost button is Rock
// Middle button is Paper
// Rightmost button is Scissors
void introduction() {
  int delayTime1 = 5000;
  int delayTime2 = 1500;
  lcd.setCursor(0, 0);
  lcd.print("ROCK, PAPER, ");
  lcd.setCursor(0, 1);
  lcd.print("SCISSORS");
  delay(delayTime1);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Play Rock,Paper,");
  lcd.setCursor(0, 1);
  lcd.print("or Scissors");
  delay(delayTime2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("each round and");
  lcd.setCursor(0, 1);
  lcd.print("try to outsmart");
  delay(delayTime2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("your opponent,");
  lcd.setCursor(0, 1);
  lcd.print("the computer.");
  delay(delayTime2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Leftmost button");
  lcd.setCursor(0, 1);
  lcd.print("is Rock");
  delay(delayTime2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Middle button");
  lcd.setCursor(0, 1);
  lcd.print("is Paper");
  delay(delayTime2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Rightmost button");
  lcd.setCursor(0, 1);
  lcd.print("is Scissors");
  delay(delayTime2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Good luck!");
  delay(delayTime2);
  lcd.clear();
}

// Take statment and split onto 16 character line (for-loop)
// void displayWords(String statement) {
//   String printStatement;
//   char firstLine[16];
//   statement.toCharArray(firstLine, 16);
//   if (printStatement[16] != ' ' ) {}
// }

void playGame() {
  lcd.setCursor(0, 0);
  lcd.print("B1=ROCK|B2=PAPER");
  lcd.setCursor(0, 1);
  lcd.print("B3=SCISSORS");

  String availableMoves[] = {"Rock", "Scissors", "Paper"};
  String outcomeStatement;
  char computerMove[8];
  char playerMove[8];
  //chooseMove(playerMove, computerMove);

  // rock, paper, scissors, shoot
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROCK ");
  delay(1000);
  lcd.print("PAPER");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("SCISSORS ");
  delay(1000);
  lcd.print("SHOOT");
  delay(250);
  lcd.clear();

  // playerMoves[0] = "Rock";
  // playerMoves[1] = "Rock";

  // if (strcmp(playerMoves[0], playerMoves[1]) == 0) {
  //   outcomeStatement = "Draw!";
  // } else {
  //   for (int choice = 0; choice < 3; choice++) {
  //     if (strcmp(playerMoves[0], availableMoves[choice]) == 0) {
  //       if (strcmp(playerMoves[1], availableMoves[(choice + 1) % 3])) == 0) {
  //         outcomeStatement = "You Lose";
  //       } else {
  //         outcomeStatement = "You Win!";
  //       }
  //     }
  //     lcd.setCursor(0, 0);
  //   lcd.print(playerMoves[0] + " " + playerMoves[1]);
  //   lcd.setCursor(0, 1);
  //   lcd.print(outcomeStatement);
  //   delay(6000);
  //   lcd.clear();
  //   }
  // }

}

// void chooseMove(char playerMove[], char computerMove[]) {
//   int delayTime = 70;
//   int counter = 0;

//   while (true) {
//     int rock = digitalRead(switch1);
//     int paper = digitalRead(switch2);
//     int scissors = digitalRead(switch3);

//     if (rock == 1){
//       moveArray[0] = "Rock";
//       moveArray[1] = computerMove(counter);
//     } else if (paper == 1) {
//       moveArray[0] = "Paper";
//       moveArray[1] = computerMove(counter);
//       break;
//     } else if (scissors == 1) {
//       moveArray[0] = "Scissors";
//       moveArray[1] = computerMove(counter);
//       break;
//     }
//     counter += 1;
//     delay(delayTime);
//   }
// }

// String computerMove(int value) {
//   if (value % 3 == 0 || value % 5 == 0 || value % 7 == 0) {
//     return "Rock";
//   } else if (value % 2 == 0) {
//     return "Paper";
//   } else {
//     return "Scissors";
//   }
// }
