// 
// Titan 9g servo controller with 16-bit Timer1, Fast PWM w/prescaler of 8, Non-Inverted
// ICR1 as TOP, OCR1 as PW, and OC1A as output pin (pin 9)

//#include <avr/interrupt.h>

#define MAX_ANGLE 4500
#define MIN_ANGLE 1000

void setup() { 

  // TCCR1A
  // Bit                7      6      5      4      3      2     1     0
  // Bit Name         COM1A1 COM1A0 COM1B1 COM1B0 -----  ----- WGM11 WGM10
  //                    1      0      0      0      0      0     1     0
  // COM1A1,COM1A0 = (1,0) for OC1 output (pin 9) Non-Inverted
TCCR1A = B10000010;

  // TCCR1B
  // Bit                7      6      5      4      3      2    1      0
  // Bit Name         ICNC1  ICES1  -----  WGM13  WGM12  CS12  CS11  CS10
  //                    0      0      0      1      1      0     1     0
  // CS12,CS11,CS10 = (0,1,0) System clock divided by 8 (prescaler)
  // WGM13,12,11,10 = (1,1,1,0)
TCCR1B = B00011010;

ICR1 = 39999; // 10 bit resolution?

pinMode (9, OUTPUT);  // OC1A/pin9

} 

void loop()
{
  turnTo(180);
  delay(2000);
  turnTo(89);
  delay(2000);
  turnTo(0);
  delay(2000);
}

void turnTo(int n) {
  //OCR1A = Pulse Width  
  OCR1A = map(constrain(n,0,180), 0, 180, MIN_ANGLE, MAX_ANGLE);
}
    

