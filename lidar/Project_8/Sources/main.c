#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "timers.h"
#include "lidar.h"
#include "simple_serial.h"


void main(void) {

  volatile unsigned int distance = 0;
  
  unsigned char buffer[12];
  
  // initialise interrupts 
  Init_TOF();
  Init_TC1();        // make it part of "Init_lidar"?
  
  // initialise serial interface  
  SCI1_Init(BAUD_9600);
  
  // set port H as output
  //DDRH = 0xFF;
  
  // set port T as input
  DDRT = 0x00;                 // make it part of "Init_lidar"?
  
  // initialise variables      // make it part of "Init_lidar"?
  reset_overflow_count();
  reset_metres();
  reset_edges_count();
  reset_start_count();
  reset_end_count();  


	EnableInterrupts;
	
	
	// trigger
	//PTH = 0x00; 
	
 
  for(;;) {
  
    distance = get_metres();
    
    // serial output distance in metres
    sprintf(buffer,"%u\r\n",distance);
    SCI1_OutString(buffer);
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
