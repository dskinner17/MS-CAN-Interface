#include <LiquidCrystal.h>
#include "TimerOne.h"
#include "mcp2515.h"

// AFR, MAP, IAT, water temp
// AFR -> id#1514 data[1]/10 (AFR)
// MAP -> id#1512 data[0-1]/10 (kPa)
// MAT -> id#1513 data[4-5]/10 (deg F)
// CLT -> id#1512 data[4-5]/10 (deg F)

//LiquidCrystal() pins
#define re = 
#define enable = 
#define d4 = 
#define d5 = 
#define d6 = 
#define d7 = 

//CAN variables
#define CANspeed = 1 //500k 
tCAN message;

//Monitoring Variables
uint8_t AFR = 0;
uint8_t MAP = 0;
uint8_t MAT = 0;
uint8_t CLT = 0;

//LCD
LiquidCrystal lcd(re, enable, d4, d5, d6, d7);

void setup() {
  setupScreen();

  mcp2515_init(CANspeed);

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(updateLCD);


}

void loop() {
  if (mcp2515_check_message()) {
    noInterrupts();
    if (mcp2515_get_message(&message)) {
      if(message.id == 1512){
        MAP = (message.data[1]<<4) || message.data[0];
        CLT = (message.data[5]<<4) || message.data[4];
      }
      else if(message.id == 1513){
        MAT = (message.data[5]<<4) || message.data[4];
      }
      else if(message.id == 1514){
        AFR = message.data[1];
      }
    }
    interrupts();
  }

}

void setupScreen() {
  lcd.begin(20, 4);
  lcd.clear();
  lcd.noCursor();
  lcd.print("Hello, World!");
}

void updateLCD() {
  lcd.clear();
  float fAFR, fMAP, fCLT, fMAT;

  fAFR = AFR/10;
  fMAP = fMAP/10;
  fCLT = CLT/10;
  fMAT = fMAT/10;

  lcd.clear();
  lcd.print("AFR: "); lcd.print(fAFR, 1);
  lcd.setCursor(0,1);
  lcd.print("MAP: "); lcd.print(fMAP, 1);
  lcd.setCursor(0,2);
  lcd.print("CLT: "); lcd.print(fCLT, 1);
  lcd.setCursor(0,3);
  lcd.print("IAT: "); lcd.print(fMAT, 1);
  
  
}

  
