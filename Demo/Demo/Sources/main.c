#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "derivative.h"      /* derivative-specific definitions */
#include "timers.h"
#include "lidar.h"
#include "simple_serial.h"
#include "iic.h"
#include "voice.h"

#include "pll.h"
#include "l3g4200d.h"
#include "accelerometer.h"



void main(void) {


  volatile unsigned int distance = 0;
  
  unsigned char buffer[12];       // buffer for serial output
  
  
  /*
  fall_output current_output;
  fall_output prev_output;
  init_fall_output(prev_output);
  */
  
  
  // initialises the lidar
  //Init_Lidar();
  InitSpeaker();
  //Init_TC7();
  
  // initialise serial interface  
  SCI1_Init(BAUD_9600); 
    
  //COPCTL = 7;

	EnableInterrupts;
	

  for(;;) {
  
    // calculate the distance from the lidar to the closest obstacle
    //enable_lidar_interrupts();
    //Init_Lidar();
    
    //distance = get_metres();                  ////////////////////////
    
    //disable_lidar_interrupts();
    distance = 0;
    
    
    /*
    current_output = fall_detect(prev_output);  ////////////////////////
    prev_output = current_output; 
    */
    
         
    voice(distance, 0);
    
    
    //enable_lidar_interrupts();
    
    
           
    // serial output distance in metres, fall boolean
    /*
    sprintf(buffer,"distance: %u, fall: %d\r\n",distance, current_output.emergency);
    SCI1_OutString(buffer);
    */

    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
