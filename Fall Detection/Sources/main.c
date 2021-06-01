#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>

#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"
#include "servo.h"


void main(void) {
  unsigned char buffer[12];
  volatile float degrees = 0;
  int error_code = NO_ERROR;
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
  
  #ifndef SIMULATION_TESTING
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR");
    SCI1_OutString(buffer);
  } else {
    sprintf(buffer, "ERROR %d");
    SCI1_OutString(buffer);    
  }
  
  #else
  
  Init_TC7();
  
  #endif
  
   
	EnableInterrupts;
  //COPCTL = 7;
  

  for(;;) {
  
     
    current_output = fall_detect(prev_output);
    
    degrees = 90+(90*current_output.prev_output.z);
    
    //tilt_servo((int)degrees);
    
    prev_output = current_output;
    
    MSDelay(100);
    // format the string of the sensor data to go the the serial
    sprintf(buffer, "%0.2f,%0.2f\r\n",current_output.prev_output.z,degrees);

    // output the data to serial
    SCI1_OutString(buffer);
 
    _FEED_COP(); /* feeds the dog */
  }/* loop forever */
  
  /* please make sure that you never leave main */
}