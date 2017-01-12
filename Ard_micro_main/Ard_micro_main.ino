#include <LiquidCrystal.h>
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
#define CANspeed = 
tCAN message;

//Monitoring Variables
uint8_t AFR = 0;
uint8_t MAP = 0;
uint8_t MAT = 0;
uint8_t CLT = 0;

void setup() {
  LiquidCrystal(re, enable, d4, d5, d6, d7);

  mcp2515_init(CANspeed)


}

void loop() {
  if (mcp2515_check_message()) {
  
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
  }

}

void screenOut() {
  
}

  
