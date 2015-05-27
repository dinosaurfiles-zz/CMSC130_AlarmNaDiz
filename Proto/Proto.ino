#include <Wire.h>
#include <LiquidCrystal.h>
/* Start Define Constants Here*/

const int btnHr=5;
int alarmHr=1;
boolean btnHrState=false;

//Pin Address of LCD
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

//transmission Address
const int DS1307 = 0x68;

String LCDLine1;
String LCDLine2;

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
   //LCD
   lcd.begin(16, 2);

   //Contrast
   analogWrite(6, 100);

   //RTC
   Wire.begin();
   Serial.begin(9600);
   Serial.print("Current Time is: ");
   printTimeSerial();
   //delay/wait for input
   //while (!Serial.available()) delay(10);

   LCDLine1 = String("");
}

void loop() {
printTimeLCD();
delay(1000);

}

byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
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
   }
   else AMPM = " AM";
   LCDLine1 =LCDLine1+ hour +":" + minute+""+AMPM+" "+months[month-1]+"."+monthday+"."+year;
   lcd.setCursor(0, 0);
   lcd.print(LCDLine1);
   lcd.setCursor(0, 1);
   LCDLine2 = LCDLine2+"Alarm: "+alarmHr+":";
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
  }
  else AMPM = " AM";
  Serial.print(hour);
  Serial.print(":");
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  Serial.println(AMPM);
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


