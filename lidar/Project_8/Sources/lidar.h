#ifndef LIDAR_HEADER
#define LIDAR_HEADER

#include "derivative.h"




void reset_metres(void);

void reset_edges_count(void);

void reset_start_count(void);

void reset_end_count(void);


volatile unsigned int get_metres(void);

volatile unsigned int get_edges_count(void);

volatile unsigned int get_distance(volatile unsigned int startTimerCount, volatile unsigned int endTimerCount);




// function to initialise the timer channel 1
void Init_TC1 (void);

// timer interrupt definition
__interrupt void TC1_ISR(void);


#endif