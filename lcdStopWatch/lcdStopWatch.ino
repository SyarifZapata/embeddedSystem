/*
  LiquidCrystal Library
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// RS,E,D4,D5,D6,D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


int button = 3;
volatile int stopwatchStatus = 0;
float startTime = 0;
float stopTime = 0;
boolean programStarted = false;
boolean screenCleared = false;
long lastInterrupt = 0;


void setup() {
  
  pinMode(button, INPUT);
  attachInterrupt(1,buttonPressed,RISING);

  
  lcd.begin(16, 2);
  
  lcd.setCursor(4, 0); // set the cursor to first character on line 1 - NOT needed (it sets automatically on lcd.begin()
  lcd.print("Arduino");
  lcd.setCursor(3, 1); // set the cursor to 4th character on line 2
  lcd.print("StopWatch");
  delay(2000); // wait 2 seconds
  lcd.clear(); // clear the display
  lcd.setCursor(3,0);
  lcd.print("By Syarif");
  lcd.setCursor(1,1);
  lcd.print(" Hidayatullah");
  delay(2000);
  lcd.clear();
  lcd.print("Press button for");
  lcd.setCursor(2, 1); // set the cursor to 3rd character on line 2
  lcd.print("Start & Stop");
}

void loop() {
 printTime();
 delay(70);
}

void buttonPressed(){
  if ((millis()-lastInterrupt) > 100){
    if(stopwatchStatus == 0){
      stopwatchStatus = 1;
      programStarted = true;
      startTime = millis();
    }else{
      stopwatchStatus = 0;
      stopTime = millis()-startTime;
    }
  }
  lastInterrupt = millis();
  screenCleared = false;
}

void printTime(){
  if(stopwatchStatus == 0 && programStarted == true){
    if(!screenCleared){
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Stopped"); 
       lcd.setCursor(0, 1);
       lcd.print(stopTime/1000,3); 
       lcd.setCursor(11, 1);
       lcd.print("sec's"); 
       screenCleared = true;
    }
  }else if(stopwatchStatus == 1){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Started"); 
    lcd.setCursor(0, 1);
    lcd.print((millis()-startTime)/1000,3); 
    lcd.setCursor(11, 1);
    lcd.print("sec's"); 
  }
    
}

