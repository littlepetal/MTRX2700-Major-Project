#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>
#include <stdlib.h>

#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"
#include "accelerometer.h"


 void main(void) {

  
  unsigned char buffer[128];
  fall_output current_output;
  fall_output prev_output;
  init_fall_output(prev_output);
  
  //assert(error_code != NO_ERROR);

  #ifndef SIMULATION_TESTING

  // make sure the board is set to 24MHz
  PLL_Init();

  #endif

   // initialise the simple serial
  SCI1_Init(BAUD_9600);
  
 
  // initialise the sensor suite
  Init_TC7();
  
   
	EnableInterrupts;
  COPCTL = 7;

  for(;;) {
  
     
     current_output = fall_detect(prev_output);
     prev_output = current_output;
     
     
     

    // format the string of the sensor data to go the the serial
    sprintf(buffer, "%d\r\n",current_output.alert);

    // output the data to serial
    SCI1_OutString(buffer);
 
    _FEED_COP(); /* feeds the dog */
  }/* loop forever */
  
  /* please make sure that you never leave main */
}