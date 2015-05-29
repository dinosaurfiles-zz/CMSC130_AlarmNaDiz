#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
        analogWrite(6, 100);
}

void loop() {
  lcd.setCursor(0, 0);
   lcd.print("Agi Si hil");

  lcd.setCursor(0, 1);
  lcd.print("CHUPA MARK");
    
}
