/*
 * Main.cpp
 *
 * Created: 11/21/2013 12:04:07 AM
 *  Author: Compaq_Administrator
 */


#ifndef SKETCH_H_
#define SKETCH_H_

#ifndef Arduino_h
#include <Arduino.h>
#endif

const int pin1 = 3;
const int pin2 = 5;
const int pin3 = 7;
const int pin4 = 9;

void setup();
void loop();

void turnClockwise(int);
void turnCounterclockwise(int);


#endif /* SKETCH_H_ */