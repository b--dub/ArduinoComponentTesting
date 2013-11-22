//  Operation of 2x16 LCD display using 8 data bits provided through 8 bit shift register 595
//  I'm using the read only method (LCD pin 5 to ground) with delays instead of looking to see
//  if the LCD is still busy.
//  
//  This code is just the basic building blocks of what could be used to create something of 
//  value later.  It isn't meant to be complete in any way... just some tooling around and testing it out


#ifndef LCD2x16_W595_H_
#include "LCD2x16_W595.h"
#endif

void setup() {
	Serial.begin(9600);                                  //  for logging/trouble shooting
	Serial.setTimeout(3000);
	lprintf("Serial connection established w/LCD");
	
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(enablePin, OUTPUT);
	pinMode(rsPin, OUTPUT);
	
	initLCD();
	loadCustomCharacters();
	writeString("Hello World!");
}

void loop() {
	Serial.println("Enter 1 to enter a cmd or 2 to enter a string to display");
	int i; String str;
	while ((i=Serial.read())==-1){}
		i-=48;
	if (i==1) {
		Serial.println("Enter Command: ");
		str = Serial.readString();
		writeCommand(str.toInt());
	}
	else if (i==2) {
		Serial.println("Enter String: ");
		str = Serial.readString();
		writeString(str);
	}
	
}

// Logging print function = printf() to Serial
void lprintf(char *fmt, ... ) {        //  Source:  http://playground.arduino.cc/Main/Printf
	char tmp[128];                       //  resulting string limited to 128 chars
	va_list args;
	va_start (args, fmt );
	vsnprintf(tmp, 128, fmt, args);
	va_end (args);
	
	logCounter++;
	Serial.print("Arduino serial log entry ");
	Serial.print(logCounter);
	Serial.print(":  ");
	Serial.println(tmp);
}


//  LCD functions for ino program: LCD2x16_Display_with_8bit_ShiftReg_595

void initLCD() {
	delay(200);
	writeCommand(B00110000);        // recommended start to init
	writeCommand(B00110000);
	writeCommand(B00110000);
	writeCommand(56);                // 2 line, 8 bits, and 5x7 dots
	writeCommand(15);                // Display on, Cursor blinking
	writeCommand(1);                 // clear LCD
	writeCommand(6);                 // Cursor move direction right, no display shift
	lprintf("LCD init completed");
}

void writeCommand(byte b) {                   // Write a command to LCD
	digitalWrite(rsPin, LOW);                   // Commands: http://www.8051projects.net/lcd-interfacing/commands.php
	writeByteToShiftRegister(b);
	digitalWrite(enablePin,LOW);
	delay(1);
	digitalWrite(enablePin, HIGH);
	delay(1);
	digitalWrite(enablePin, LOW);
	delay(20);
	lprintf("COMMAND %d written to LCD", b);
}

void writeChar(char c) {                      // Write a character to LCD
	digitalWrite(rsPin, HIGH);
	writeCharToShiftRegister(c);
	digitalWrite(enablePin,LOW);
	delay(1);
	digitalWrite(enablePin, HIGH);
	delay(1);
	digitalWrite(enablePin, LOW);
	delay(20);
	lprintf("CHARACTER %c written to LCD", c);
}

void writeString(String str) {
	for (int i = 0;i<str.length(); ++i)
		writeChar(str.charAt(i));
}

void clearLCD() {
	writeCommand(1);
	lprintf("LCD screen and DDRAM cleared");
}

void returnCursorHome() {
	digitalWrite(rsPin, LOW);
	//digitalWrite(rwPin, LOW);
	writeByteToShiftRegister(B00000001);
	digitalWrite(enablePin, HIGH);
	delay(20);
	digitalWrite(enablePin, LOW);
	delay(20);
	lprintf("Cursor returned home");
}

void shiftDisplayLeft() {
	writeCommand(24);
}
void shiftDisplayRight(){
	writeCommand(30);
}
void moveCursorLeft(){
	writeCommand(16);
}
void moveCursorRight(){
	writeCommand(20);
}

//  TODO  add other commands from table here http://www.8051projects.net/lcd-interfacing/commands.php


//  595 Shift Register functions for ino program: LCD2x16_Display_with_8bit_ShiftReg_595

void writeByteToShiftRegister(byte b) {
	for (int i = 0; i < 8; ++i) {
		digitalWrite(dataPin, (b& (1<<i)));
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin, LOW);
	lprintf("Wrote byte %d to shift register", b);
}

void writeCharToShiftRegister(char c) {
	for (int i = 0; i < 8; ++i) {
		digitalWrite(dataPin, (c& (1<<i)));
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin, LOW);
	lprintf("Wrote character %c to shift register", c);
}





