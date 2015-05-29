#include <Wire.h>
#include <LiquidCrystal.h>
#include <Pitches.h>;

/* Start Define Constants Here*/

/* Alarm Sound */
#include "Pitches.h"

// notes in the melody:
int melody[] = {
        NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4
};


int compareHr;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
        4, 8, 8, 4,4,4,4,4
};
/* Alarm Sound */

int gameSequence[] = {0,0,0,0,0};
int inputSequence[] = {0,0,0,0,0};
int pushButton = 0;
bool correctseq = false;

const int LED1 = 5;
const int LED2 = 4;
const int LED3 = 3;
const int LED4 = 2;

int anBtn1 = 0;
int anBtn2 = 1;
int anBtn3 = 2;
int anBtn4 = 3;

int alarmHr = 0;
int alarmMin = 0;

String alarmHrStr = "";
String alarmMinStr = "";

String AD = "";

//Pin Address of LCD
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

//transmission Address
const int DS1307 = 0x68;

String LCDLine1 = "";
String LCDLine2 = "";

//For
const char* days[] =
{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* months[] =
{"01", "02", "03", "04", "05", "06", "07", "08","09", "10", "11", "12"};

//Initial Time values
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;

/* End Define Constants Here*/

void setup() {
        //Buttons
        pinMode(A0,INPUT_PULLUP);
        pinMode(A1,INPUT_PULLUP);
        pinMode(A2,INPUT_PULLUP);
        pinMode(A3,INPUT_PULLUP);

        //LED
        pinMode(LED1, OUTPUT);
        pinMode(LED2, OUTPUT);
        pinMode(LED3, OUTPUT);
        pinMode(LED4, OUTPUT);

        //LCD
        lcd.begin(16, 2);

        //Contrast
        analogWrite(6, 100);

        //RTC
        Wire.begin();
        Serial.begin(9600);

        dispOnLCD("Set Time On",0);
        dispOnLCD("Serial Monitor",1);


        Serial.print("Current Time is: ");
        printTimeSerial();
        Serial.println("Please change to newline ending the settings on the lower right of the Serial Monitor");
        Serial.println("Would you like to set the date and time now? Y/N");

        while (!Serial.available()) delay(10);
        if (Serial.read() == 'y' || Serial.read() == 'Y')

        // This set of functions allows the user to change the date and time
        {
                Serial.read();
                setTime();
                Serial.print("The current date and time is now: ");
                printTimeSerial();
        }
        lcd.clear();
        Serial.println("Thank you.");

        dispOnLCD("Set Alarm",0);
        dispOnLCD("On LCD",1);
        Serial.println("Set Alarm? Y/N (Default = 00:00)");

        while (!Serial.available()) delay(10);
        if (Serial.read() == 'y' || Serial.read() == 'Y') {
                Serial.print("Alarm Hour (0-23):");
                Serial.read();
                alarmHr = readByte();
                Serial.println(alarmHr);
                Serial.print("Alarm minute (0-59):");
                Serial.read();
                alarmMin = readByte();
                Serial.println(alarmMin);
        }
        Serial.println("Alarm has been set");
}


void loop() {
   if (AD == "PM"){
      compareHr = hour+12;
   }else compareHr = hour;

   if (alarmHr == compareHr && alarmMin == minute){
      //playtune();
      dispOnLCD("ALARM STARTING", 0);
      dispOnLCD("GAME START",1);
      if (correctseq != 1){
       //  playtune();
      }
      //playtune();
   }else{
      printTimeLCD();
   }


}

void gameStart(){
        for  (int i =0; i <5; i++) {
                gameSequence[i] = random (1,5);
        }
        playOnLed();
        while(pushButton < 5 ) {
                if(analogRead(0)>1000) {
                        LedLight(1);
                        delay(200);
                        inputSequence[pushButton]=1;
                        pushButton++;
                }else if(analogRead(1)>1000) {
                        LedLight(2);
                        delay(200);
                        inputSequence[pushButton]=2;
                        pushButton++;
                }else if(analogRead(2)>1000) {
                        LedLight(3);
                        delay(200);
                        inputSequence[pushButton]=3;
                        pushButton++;
                }else if(analogRead(3)>1000) {
                        LedLight(4);
                        delay(200);
                        inputSequence[pushButton]=4;
                        pushButton++;
                }else {}


        }
        for (int j = 0; j < 5; j++) {
                if (gameSequence[j] != inputSequence[j]) {
                        correctseq = false;
                }else{
                        correctseq = true;
                }

        }
        if (correctseq != 1){
           gameStart();
       }


        pushButton=0;
        Serial.println(correctseq);
}

void playOnLed(){
        for (int i = 0; i <6; i++) {
                LedLight(gameSequence[i]);
        }
}

void LedLight(int lednum){
        if (lednum == 1) {
                digitalWrite(LED1, HIGH);
                delay(250);
                digitalWrite(LED1, LOW);
                delay(250);
        }else if (lednum == 2) {
                digitalWrite(LED2, HIGH);
                delay(250);
                digitalWrite(LED2, LOW);
                delay(250);
        }else if (lednum == 3) {
                digitalWrite(LED3, HIGH);
                delay(250);
                digitalWrite(LED3, LOW);
                delay(250);
        }else if (lednum == 4) {
                digitalWrite(LED4, HIGH);
                delay(250);
                digitalWrite(LED4, LOW);
                delay(250);
        }else {}
}

void dispOnLCD(String msg, int pos){
        lcd.setCursor(0, pos);
        lcd.print(msg);
}

void playtune(){
        for (int thisNote = 0; thisNote < 8; thisNote++) {

                int noteDuration = 1000/noteDurations[thisNote];

                // (pin number, melody, noteduraion)
                tone(13, melody[thisNote],noteDuration);

                int pauseBetweenNotes = noteDuration * 1.30;
                delay(pauseBetweenNotes);
                noTone(8);
        }
}

byte decToBcd(byte val) {
        return ((val/10*16) + (val%10));
}

byte bcdToDec(byte val) {
        return ((val/16*10) + (val%16));
}

void setTime() {
        Serial.print("Please enter the current year, 00-99. - ");
        year = readByte();
        Serial.println(year);
        Serial.print("Please enter the current month, 1-12. - ");
        month = readByte();
        Serial.println(months[month-1]);
        Serial.print("Please enter the current day of the month, 1-31. - ");
        monthday = readByte();
        Serial.println(monthday);
        Serial.println("Please enter the current day of the week, 1-7.");
        Serial.print("1 Sun | 2 Mon | 3 Tues | 4 Weds | 5 Thu | 6 Fri | 7 Sat - ");
        weekday = readByte();
        Serial.println(days[weekday-1]);
        Serial.print("Please enter the current hour in 24hr format, 0-23. - ");
        hour = readByte();
        Serial.println(hour);
        Serial.print("Please enter the current minute, 0-59. - ");
        minute = readByte();
        Serial.println(minute);
        second = 0;
        Serial.println("The data has been entered.");

        // The following codes transmits the data to the RTC
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0));
        Wire.write(decToBcd(second));
        Wire.write(decToBcd(minute));
        Wire.write(decToBcd(hour));
        Wire.write(decToBcd(weekday));
        Wire.write(decToBcd(monthday));
        Wire.write(decToBcd(month));
        Wire.write(decToBcd(year));
        Wire.write(byte(0));
        Wire.endTransmission();
        // Ends transmission of data
}

byte readByte() {
        while (!Serial.available()) delay(10);
        byte reading = 0;
        byte incomingByte = Serial.read();
        while (incomingByte != '\n') {
                if (incomingByte >= '0' && incomingByte <= '9')
                        reading = reading * 10 + (incomingByte - '0');
                else;
                incomingByte = Serial.read();
        }
        Serial.flush();
        return reading;
}

void printTimeLCD(){
        char buffer[3];
        const char* AMPM = 0;
        readTime();
        LCDLine1="";
        LCDLine2="";
        if (hour > 12) {
                hour -= 12;
                AMPM = " PM";
                AD = "PM";
        }
        else{
           AMPM = " AM";
           AD = "AM";
        }
        LCDLine1 =LCDLine1+ hour +":" + minute+""+AMPM+" "+months[month-1]+"."+monthday+"."+year;
        lcd.setCursor(0, 0);
        lcd.print(LCDLine1);
        lcd.setCursor(0, 1);
        alarmHrStr = "";
        if (alarmHr<10) {
                alarmHrStr = alarmHrStr+"0"+alarmHr;
        }else{
                alarmHrStr = alarmHrStr+alarmHr;
        }
        alarmMinStr = "";
        if (alarmMin<10) {
                alarmMinStr = alarmMinStr+"0"+alarmMin;
        }else{
                alarmMinStr = alarmMinStr+alarmMin;

        }
        LCDLine2 = LCDLine2+"Alarm: "+alarmHrStr+":"+alarmMinStr;
        lcd.print(LCDLine2);

}

void printTimeSerial() {
        char buffer[3];
        const char* AMPM = 0;
        readTime();
        Serial.print(days[weekday-1]);
        Serial.print(" ");
        Serial.print(months[month-1]);
        Serial.print(" ");
        Serial.print(monthday);
        Serial.print(", 20");
        Serial.print(year);
        Serial.print(" ");
        if (hour > 12) {
                hour -= 12;
                AMPM = " PM";
                AD = "PM";
        }
        else {
           AMPM = " AM";
           AD = "AM";
        }
        Serial.print(hour);
        Serial.print(":");
        sprintf(buffer, "%02d", minute);
        Serial.print(buffer);
        Serial.println(AMPM);
}

void readTime() {
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0));
        Wire.endTransmission();
        Wire.requestFrom(DS1307, 7);
        second = bcdToDec(Wire.read());
        minute = bcdToDec(Wire.read());
        hour = bcdToDec(Wire.read());
        weekday = bcdToDec(Wire.read());
        monthday = bcdToDec(Wire.read());
        month = bcdToDec(Wire.read());
        year = bcdToDec(Wire.read());
}
