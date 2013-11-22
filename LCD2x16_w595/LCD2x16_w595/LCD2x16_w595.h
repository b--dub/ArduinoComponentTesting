//  Custom characters for ino program: LCD2x16_Display_with_8bit_ShiftReg_595

#ifndef LCD2x16_W595_H_
#define LCD2x16_W595_H_

#ifndef Arduino_h
#include <Arduino.h>
#endif

int clockPin = 3;          // 595 clock(11) - cycle once for each bit
int latchPin = 5;          // 595 latch(12) - cycle once for each word
int dataPin = 7;           // 595 data(14) - serial to parallel input
int rsPin = 9;             // LCD RS - LOW for Command Input, HIGH for Data Input
int enablePin = 11;        // LCD enable - cycle once for each command or Char
          

int logCounter = 0;

void setup();
void loop();

void initLCD();
void writeCommand(byte);
void writeChar(char);
void writeString(String);
void clearLCD();
void returnCursorHome();
void shiftDisplayLeft();
void shiftDisplayRight();
void moveCursorLeft();
void moveCursorRight();

void writeByteToShiftRegister(byte);
void writeCharToShiftRegister(char);

void lprintf(char *fmt, ... );

void loadCustomCharacters() {            //  up to 8 characters can be created and stored in CGRAM
  int customCharacterCounter = 0;
  
  byte char1[8] = {                      // just lines
    B11111, 
    B00000,  
    B11111, 
    B00000, 
    B11111, 
    B00000, 
    B11111, 
    B00000 };

    byte char2[8] = {                      // Square
    B11111, 
    B10001,  
    B10001, 
    B10001, 
    B10001, 
    B10001, 
    B11111, 
    B00000 };
    
    byte char3[8] = {                      // Big Diamond
    B00100, 
    B01110,  
    B01110, 
    B11111, 
    B01110, 
    B01110, 
    B00100, 
    B00000 };
    
    byte char4[8] = {                      // Little Diamond
    B00000, 
    B00000,  
    B00100, 
    B01110, 
    B00100, 
    B00000, 
    B00000, 
    B00000 };
    
    byte char5[8] = {                      // up arrow
    B00100, 
    B01110,  
    B11111, 
    B00100, 
    B00100, 
    B00100, 
    B00100, 
    B00000 };
    
    byte char6[8] = {                      // point right
    B01000, 
    B01100,  
    B01110, 
    B01111, 
    B01110, 
    B01100, 
    B01000, 
    B00000 };
    
    byte char7[8] = {                      // point left
    B00010, 
    B00110,  
    B01110, 
    B11110, 
    B01110, 
    B00110, 
    B00010, 
    B00000 };
    
    byte char8[8] = {                      // down arrow
    B00100, 
    B00100,  
    B00100, 
    B00100, 
    B11111, 
    B01110, 
    B00100, 
    B00000 };
    
  lprintf("%d Custom characters loaded", customCharacterCounter); 
}

#endif // LCD2X16_FROM_595_H

