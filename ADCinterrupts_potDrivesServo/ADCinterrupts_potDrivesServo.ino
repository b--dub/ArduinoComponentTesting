// POT - 50k pot inputs to ADC with interrupts to control servo position 0-180 deg
// SERVO - Titan 9g servo controller with 16-bit Timer1, Fast PWM w/prescaler of 8, Non-Inverted
//         ICR1 as TOP, OCR1 as PW, and OC1A as output pin (pin 9)

//#include <avr/io.h>
//#include <avr/interrupt.h>

#define MAX_ANGLE 4500
#define MIN_ANGLE 1000

void setup() { 

//////////////////  PWM    /////////////////////////////////////////////////////////////

  // TCCR1A
  // Bit                7      6      5      4      3      2     1     0
  // Bit Name         COM1A1 COM1A0 COM1B1 COM1B0 -----  ----- WGM11 WGM10
  //                    1      0      0      0      0      0     1     0
  // COM1A[1:0] = (1,0) for OC1 output (pin 9) Non-Inverted
TCCR1A = B10000010;

  // TCCR1B
  // Bit                7      6      5      4      3      2    1      0
  // Bit Name         ICNC1  ICES1  -----  WGM13  WGM12  CS12  CS11  CS10
  //                    0      0      0      1      1      0     1     0
  // CS[12:10] = (0,1,0) System clock divided by 8 (prescaler)
  // WGM[13:10] = (1,1,1,0)
TCCR1B = B00011010;

ICR1 = 39999;          // pwm period for SERVO (TOP)
DDRB |= 1<<DDB1;       // OC1A/pin9 for pwm signal to SERVO


////////////////////  ADC  //////////////////////////////////////////////////////////////

  // ADMUX
  // Bit      7     6     5     4    3    2    1     0
  // (0x7C) REFS1 REFS0 ADLAR   –   MUX3 MUX2 MUX1 MUX0 
  //         R/W   R/W   R/W    R   R/W  R/W  R/W  R/W
  // Initial  0     0     0      0    0    0    0     0
  // REFS[1:0] = (0,1) - Voltage Reference Selection - AVCC
  // ADLAR = (0) - Don't Left Adjust Result - 2 MSBs in ADCH register
  // MUX[3:0] = (0,0,0,0) - ADC0 (Analog Input pin 0)
ADMUX |= 1<<REFS0;

  // ADCSRA
  // Bit     7      6       5      4      3       2       1       0
  // (0x7A) ADEN   ADSC   ADATE   ADIF   ADIE   ADPS2   ADPS1   ADPS0  
  //        R/W    R/W     R/W    R/W    R/W     R/W     R/W     R/W
  // Initial 0      0       0      0      0       0       0       0
  // ADEN = (1) - ADC Enabled
  // ADIE = (1) - ADC Conversion Complete Interrupt Enabled
  // ADPS[2:0] = (1,1,1) - ADC Prescaler to 128 - the minimum for 16MHz system clock
ADCSRA |= 1<<ADEN | 1<<ADIE | 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;

  // ADCSRB
  // Bit    7  6    5   4   3     2    1     0
  // (0x7B) – ACME  –   –   –   ADTS2 ADTS1 ADTS0
  //        R R/W   R   R   R   R/W   R/W   R/W
  // Init   0  0    0   0   0     0    0     0
  // ADTS[2:0] = (0,0,0) - ADC Auto Trigger Source (Free running)
ADCSRB |= 0;



sei();  // Enable Global Interrupts
ADCSRA |= 1<<ADSC;  //  Start ADC conversion
} 

void loop()
{
  
}

void turnTo(int n) {
  //OCR1A = Output Compare Register 1A - Pulse Width  
  OCR1A = map(constrain(n,0,1023), 0, 1023, MIN_ANGLE, MAX_ANGLE);
}
    
ISR(ADC_vect) {
  int low = ADCL;
  turnTo(ADCH<<8 | low);      // Read converion output
  ADCSRA |= 1<<ADSC;  //  Start ADC conversion
}
    

