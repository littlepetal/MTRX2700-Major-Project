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
  
  // initialises the lidar
  Init_Lidar();
  
  // initialise serial interface  
  SCI1_Init(BAUD_9600);


	EnableInterrupts;
	
 
  for(;;) {
    // calculate the distance from the lidar to the closest obstacle
    distance = get_metres();
    
    // serial output distance in metres
    sprintf(buffer,"%u\r\n",distance);
    SCI1_OutString(buffer);
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
