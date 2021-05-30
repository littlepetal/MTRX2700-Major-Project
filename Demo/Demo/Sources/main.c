#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "timers.h"
#include "lidar.h"
#include "simple_serial.h"
#include "iic.h"
#include "voice.h"


void main(void) {




  volatile unsigned int distance = 0;
  //volatile unsigned int fall = 0;
  
  unsigned char buffer[12];       // buffer for serial output

  
  
  // initialises the lidar
  Init_Lidar();
  InitSpeaker();
  
  // initialise serial interface  
  SCI1_Init(BAUD_9600); 


	EnableInterrupts;


  for(;;) {
  
    // calculate the distance from the lidar to the closest obstacle
    //enable_lidar_interrupts();
    //Init_Lidar();
    
    distance = get_metres();
    //disable_lidar_interrupts();
    //distance = 23;
   
       
    //fall = fallDetect();
      
    //InitSpeaker();  
    //voice(distance, 0);
    
    //enable_lidar_interrupts();
      
  
    
    // serial output distance in metres
    sprintf(buffer,"%u\r\n",distance);
    SCI1_OutString(buffer);
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
