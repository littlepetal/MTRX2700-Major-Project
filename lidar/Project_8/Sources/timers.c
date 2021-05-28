#include "timers.h"
#include <math.h>
#include "derivative.h"
#include <hidef.h>




volatile unsigned int numberOfOverflows = 0;


// set the number of timer overflows to zero
void reset_overflow_count(void) {
    numberOfOverflows = 0;
}


// returns the timer overflow count
volatile unsigned int get_overflow_count(void){
    return numberOfOverflows;
}




// set up the timers for timer overflow to use the interrupt
void Init_TOF (void) {  
    TSCR1=0x80;
    TSCR2=0x84;   
}

// added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */

// interrupt is triggered when there is a timer count overflow
__interrupt void TOF_ISR(void) {     
    numberOfOverflows += 1;        // increment overflow count    
    TFLG2 = 0x80;
} 


// set up the timers for channel 1 to use the interrupt
void Init_TC1 (void) {
  TSCR1=0x80;
  TSCR2=0x84;
  
  TIOS =0x00;     // set channel 1 to input capture
  
  // capture on both falling and rising edge
  TCTL4_EDG1A = 1;
  TCTL4_EDG1B = 1; 
  
  TIE=0x02;       // enable channel 1 interrupt
}


        
