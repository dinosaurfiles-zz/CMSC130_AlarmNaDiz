const int buttonPin0 = 2; 
const int ledPin0 = 6;      

const int buttonPin1 = 3;    
const int ledPin1 = 7;      

const int buttonPin2 = 4;    
const int ledPin2 = 8;      

const int buttonPin3 = 5;    
const int ledPin3 = 9;      

// Variables will change:
int ledState0 = LOW;         
int buttonState0;             
int lastButtonState0 = LOW;   

int ledState1 = LOW;         
int buttonState1;             
int lastButtonState1 = LOW;   

int ledState2 = LOW;         
int buttonState2;             
int lastButtonState2 = LOW;   

int ledState3 = LOW;         
int buttonState3;             
int lastButtonState3 = LOW;   

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin0, INPUT);
  pinMode(ledPin0, OUTPUT);
  
  pinMode(buttonPin1, INPUT);
  pinMode(ledPin1, OUTPUT);
  
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin2, OUTPUT);
  
  pinMode(buttonPin3, INPUT);
  pinMode(ledPin3, OUTPUT);
  
  // set initial LED state
  digitalWrite(ledPin0, ledState0);
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  
}

boolean debounce(boolean last, int btnNum){
  if (btnNum ==0){
      boolean current = digitalRead(buttonPin0);
      if (last != current)                  
      {
        delay(5);                           
        current = digitalRead(buttonPin0);      
      }
      return current;                       

  }else if (btnNum == 1){
  
  }else if (btnNum == 2){
  
  }else if (btnNum == 3){
  
  }
}

void loop() {
  if (digitalRead(buttonPin0) == HIGH ){
    digitalWrite(ledPin0, HIGH);
    delay(100);
    digitalWrite(ledPin0, LOW);
  }else if (digitalRead(buttonPin1) == HIGH ){
    digitalWrite(ledPin1, HIGH);
    delay(100);
    digitalWrite(ledPin1, LOW);
  }else if (digitalRead(buttonPin2) == HIGH ){
    digitalWrite(ledPin2, HIGH);
    delay(100);
    digitalWrite(ledPin2, LOW);
  }else if (digitalRead(buttonPin3) == HIGH ){
    digitalWrite(ledPin3, HIGH);
    delay(100);
    digitalWrite(ledPin3, LOW);
  }
  

}

