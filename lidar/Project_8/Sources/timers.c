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
