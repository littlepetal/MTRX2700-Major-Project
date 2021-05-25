#include "timers.h"
#include <math.h>
#include "derivative.h"
#include <hidef.h>



volatile unsigned int numberOfOverflows = 0;
volatile unsigned int edgesCount = 0;
volatile unsigned int startCount = 0;
volatile unsigned int endCount = 0;
volatile unsigned int metres = 0;

// set the number of the overflows to zero
void reset_overflow_count(void) {
    numberOfOverflows = 0;
}

// set the number of the overflows to zero
void reset_edges_count(void) {
    edgesCount = 0;
}

// set the number of the overflows to zero
void reset_start_count(void) {
    startCount = 0;
}

// set the number of the overflows to zero
void reset_end_count(void) {
    endCount = 0;
}

// set the number of the overflows to zero
void reset_metres(void) {
    metres = 0;
}

// returns the overflow count
volatile unsigned int get_overflow_count(void){
    return numberOfOverflows;
}

// returns the overflow count
volatile unsigned int get_edges_count(void){
    return edgesCount;
}


volatile unsigned int get_distance(volatile unsigned int startTimerCount, volatile unsigned int endTimerCount){
    volatile unsigned int overflows = get_overflow_count();    
    volatile unsigned int maxTimerCount = 65536;
    //volatile float prescaler = 2.0;
    
    volatile unsigned int timeCount = (endTimerCount - startTimerCount + (overflows*maxTimerCount));
    
    volatile unsigned int distance = timeCount*(16.0/24000.0);
    
    reset_overflow_count();
        
    return distance;    
}





// set up the timers for timer overflow to use the interrupt
void Init_TOF (void) {  
    TSCR1=0x80;
    TSCR2=0x84;   
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
  TSCR2=0x84;
  
  TIOS =0x00;     // set channel 1 to input capture
  //TCTL4 =0x08;   // capture on falling edge only
  TCTL4_EDG1A = 1;
  TCTL4_EDG1B = 1; 
  TIE=0x02;       // enable channel 1 interrupt
}

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC1_ISR(void) { 
  
  if(PTIT_PTIT1 == 0){
    startCount = TC1;
  }
  if(PTIT_PTIT1 == 1){
    endCount = TC1;
    metres = get_distance(startCount, endCount);
  }

  //need to toggle rising/falling
  //TCTL4 = TCTL4 ^ TCTL4_EDG1A_MASK;
  //TCTL4 = TCTL4 ^ TCTL4_EDG1B_MASK;  
    
  TFLG1_C1F = 1;
  edgesCount += 1;
  
} 



/*
void Init_TC2 (void) {
  // set up the timers for channel 2 to use the interrupt
  TSCR1=0x80;
  TSCR2=0x81;
  
  TIOS =0x00;     // set channel 2 to input capture
  TCTL4 =0x10;   // capture on rising edge only
  TIE=0x04;       // enable channel 2 interrupt
}  */
    
// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC2_ISR(void) { 
  
  
  //need to toggle 
  
  
  TC2 =TCNT + (word)62500;    // 12 Hhz and PT7
  TFLG1=TFLG1 | TFLG1_C2F_MASK;
  edgesCount += 1;
  
}    */            





        

    


