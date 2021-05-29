#ifndef TIMERS_HEADER
#define TIMERS_HEADER

#include "derivative.h"


// sets the number of timer overflows to zero
void reset_overflow_count(void);

                    
// returns the overflow count
volatile unsigned int get_overflow_count(void);




// function to initialise the timer
void Init_TOF (void);

// timer interrupt definition
__interrupt void TOF_ISR(void); 


#endif