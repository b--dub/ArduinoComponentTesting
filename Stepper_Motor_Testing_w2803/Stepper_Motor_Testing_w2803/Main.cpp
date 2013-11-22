/*
 * Main.cpp powers 24BYJ48 5-Wire 4-Phase 12V Stepper Motor
 * The only operational method that seems to work is 1 Phase 2 Phase (1/12/2/23/3/34/4/41)
 * Also, delay periods shorter than .9ms have problems starting if they work at all.  ~3-4 Secs/Rotation
 *
 * Wiring colors to pins for this motor: RED-COM(12V) ORANGE-1 YELLOW-2 PURPLE-3 BLACK-4
 * 
 * Created: 11/21/2013 12:04:07 AM
 * Author: Brad Walsh
 */


#ifndef SKETCH_H_
#include "Sketch.h"
#endif


 void setup() {
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	
 }

 void loop() { 
	 
	 turnClockwise(1000);
	 
	 
 }
 
 void turnClockwise(int del) {						// Delay should be kept above 900us 
	
		 digitalWrite(pin4, HIGH);  // 4
		 delayMicroseconds(del);
		 
		 digitalWrite(pin3, HIGH);	// 43
		 delayMicroseconds(del);
		 
		 digitalWrite(pin4, LOW);	// 3
		 delayMicroseconds(del);
		 
		 digitalWrite(pin2, HIGH);	// 32
		 delayMicroseconds(del);
		 
		 digitalWrite(pin3, LOW);	// 2
		 delayMicroseconds(del);
		 
		 digitalWrite(pin1, HIGH);	// 21
		 delayMicroseconds(del);
		 
		 digitalWrite(pin2, LOW);	// 1
		 delayMicroseconds(del);
		 
		 digitalWrite(pin4, HIGH);	// 14
		 delayMicroseconds(del);
		 
		 digitalWrite(pin1, LOW);	// 4
	 
 }
 
 void turnCounterclockwise(int del) {					// Delay should be kept above 900us 
	 
	 digitalWrite(pin1, HIGH);  // 1
	 delayMicroseconds(del);
	 
	 digitalWrite(pin2, HIGH);	// 12
	 delayMicroseconds(del);
	 
	 digitalWrite(pin1, LOW);	// 2
	 delayMicroseconds(del);
	 
	 digitalWrite(pin3, HIGH);	// 23
	 delayMicroseconds(del);
	 
	 digitalWrite(pin2, LOW);	// 3
	 delayMicroseconds(del);
	 
	 digitalWrite(pin4, HIGH);	// 34
	 delayMicroseconds(del);
	 
	 digitalWrite(pin3, LOW);	// 4
	 delayMicroseconds(del);
	 
	 digitalWrite(pin1, HIGH);	// 41
	 delayMicroseconds(del);
	 
	 digitalWrite(pin4, LOW);	// 1
	 
 }
 
 