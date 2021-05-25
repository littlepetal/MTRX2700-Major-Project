#include "timers.h"
#include <math.h>
#include "derivative.h"
#include <hidef.h>



volatile unsigned int numberOfOverflows = 0;
volatile unsigned int edgesCount = 0;

// set the number of the overflows to zero
void reset_overflow_count(void) {
    numberOfOverflows = 0;
}

// set the number of the overflows to zero
void reset_edges_count(void) {
    edgesCount = 0;
}

// returns the overflow count
volatile unsigned int get_overflow_count(void){
    return numberOfOverflows;
}

// returns the overflow count
volatile unsigned int get_edges_count(void){
    return edgesCount;
}






// set up the timers for timer overflow to use the interrupt
void Init_TOF (void) {  
    TSCR1=0x80;
    TSCR2=0x81;   
}


// added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */

// interrupt is triggered when there is a timer count overflow
// overflows do happen during the operations, this wasn't working properly on Tuesday
__interrupt void TOF_ISR(void) {
     
    numberOfOverflows += 1;        // increment overflow count    
    TFLG2 = 0x80;
} 





void Init_TC1 (void) {
  // set up the timers for channel 1 to use the interrupt
  TSCR1=0x80;
  TSCR2=0x81;
  
  TIOS =0x00;     // set channel 1 to input capture
  TCTL4 =0x08;   // capture on falling edge only
  TIE=0x02;       // enable channel 1 interrupt
}

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC1_ISR(void) { 
  
  
  //need to toggle rising/falling
  TCTL4 = TCTL4 ^ TCTL4_EDG1A_MASK;
  TCTL4 = TCTL4 ^ TCTL4_EDG1B_MASK;  
  
  
  
  TC1 =TCNT + (word)62500;    // 12 Hhz and PT7
  TFLG1=TFLG1 | TFLG1_C1F_MASK;
  edgesCount += 1;
  
}    

    


