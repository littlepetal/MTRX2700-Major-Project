#ifndef LIDAR_HEADER
#define LIDAR_HEADER

#include "derivative.h"


// initialises the lidar module
void Init_Lidar (void);


void enable_lidar_interrupts(void);
void disable_lidar_interrupts(void);



// sets the number of metres to zero                                // make it part of "Init_lidar"?
void reset_metres(void);

// sets the number of edges encountered to zero                     // place in private interface?
void reset_edges_count(void);

// sets the starting timer count to zero                            // place in private interface?
void reset_start_count(void);

// sets the ending timer count to zero                              // place in private interface?
void reset_end_count(void);




// returns the number of metres away from obstacle
volatile unsigned int get_metres(void);

// returns the number edges encountered in the PWM so far           // place in private interface/testing module?
volatile unsigned int get_edges_count(void);

// calculates the distance from the obstacle in front using data provided by the lidar
volatile unsigned int get_distance(volatile unsigned int startTimerCount, volatile unsigned int endTimerCount);




// function to initialise the timer channel 1                        // make it part of "Init_lidar"?
void Init_TC1 (void);

// timer interrupt definition                                        // place in private interface/testing module?
__interrupt void TC1_ISR(void);





#endif