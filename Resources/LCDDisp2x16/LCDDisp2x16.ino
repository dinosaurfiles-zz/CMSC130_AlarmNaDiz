#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  analogWrite(10,100);
}

void loop() {
  lcd.setCursor(0, 0);
   lcd.print("Sample: agi mangud");

  lcd.setCursor(0, 1);
  lcd.print("Si ryan");
    
}
