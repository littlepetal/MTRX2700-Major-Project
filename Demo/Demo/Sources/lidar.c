#include "lidar.h"
#include "timers.h"
#include <math.h>
#include "derivative.h"
#include <hidef.h>




volatile unsigned int metres = 0;
volatile unsigned int edgesCount = 0;
volatile unsigned int startCount = 0;
volatile unsigned int endCount = 0;




// initialises the lidar module
void Init_Lidar (void){
  // initialise interrupts
  Init_TOF();
  Init_TC1();
  
  // set port T as input
  DDRT = 0x00;
  
  // initialise variables
  reset_overflow_count();
  reset_metres();
  reset_edges_count();
  reset_start_count();
  reset_end_count(); 

}

void enable_lidar_interrupts(void){
  Init_TOF();
  Init_TC1();
  DDRT = 0x00;
}
void disable_lidar_interrupts(void){
  TIE = 0x00;
}

/*
void enable_speaker_interrupts(void){
  //Init_TC1();
}
void disable_speaker_interrupts(void){
  TIE = 0x00;
}
*/




// sets the number of metres to zero
void reset_metres(void) {
    metres = 0;
}

// sets the number of edges encountered to zero             
void reset_edges_count(void) {
    edgesCount = 0;
}

// sets the starting timer count to zero                    
void reset_start_count(void) {
    startCount = 0;
}

// sets the ending timer count to zero                       
void reset_end_count(void) {
    endCount = 0;
}


// returns the number of metres away from obstacle
volatile unsigned int get_metres(void){
    return metres;
}

// returns the number edges encountered in the PWM so far     
volatile unsigned int get_edges_count(void){
    return edgesCount;
}


// calculates the distance from the obstacle in front using data provided by the lidar
volatile unsigned int get_distance(volatile unsigned int startTimerCount, volatile unsigned int endTimerCount){
    volatile unsigned int overflows = get_overflow_count();    
    volatile unsigned int maxTimerCount = 65536;
    //volatile float prescaler = 2.0;
    
    volatile unsigned int timeCount = (endTimerCount - startTimerCount + (overflows*maxTimerCount));
    
    //volatile unsigned int distance = timeCount*(16.0/24000.0);
    volatile unsigned int distance = timeCount*(128.0/24000.0);
    
    reset_overflow_count();
        
    return distance;    
}




// sets up the timers for channel 1 to use the interrupt
void Init_TC1 (void) {
  TSCR1=0x80;
  //TSCR2=0x84;
  TSCR2=0x87;
  
  TIOS =0x00;     // set channel 1 to input capture
  
  // capture on both falling and rising edge
  TCTL4_EDG1A = 1;
  TCTL4_EDG1B = 1; 
  
  TIE=0x02;       // enable channel 1 interrupt
}

//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC1_ISR(void) { 
  
  // if PT1 is high, assume a falling edge is detected, record starting timer count
  if(PTIT_PTIT1 == 1){
    startCount = TC1;
  }
  
  // if PT1 is low, assume a rising edge is detected, record ending timer count
  if(PTIT_PTIT1 == 0){
    endCount = TC1;
    metres = get_distance(startCount, endCount);
  } 
    
  TFLG1_C1F = 1;
  edgesCount += 1;  
} 
