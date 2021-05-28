#ifndef TIMERS_HEADER
#define TIMERS_HEADER

#include "derivative.h"


void reset_overflow_count(void);

void reset_edges_count(void);

void reset_start_count(void);

void reset_end_count(void);

void reset_metres(void);

volatile unsigned int get_edges_count(void);
                    
// returns the overflow count
volatile unsigned int get_overflow_count(void);

volatile unsigned int get_distance(volatile unsigned int startTimerCount, volatile unsigned int endTimerCount);

volatile unsigned int get_metres(void);

// function to initialise the timer
void Init_TOF (void);

// timer interrupt definition
__interrupt void TOF_ISR(void);

// function to initialise the timer
//void Init_TC2 (void);

// timer interrupt definition
//__interrupt void TC2_ISR(void);  


// function to initialise the timer
void Init_TC1 (void);

// timer interrupt definition
__interrupt void TC1_ISR(void);

 






#endif