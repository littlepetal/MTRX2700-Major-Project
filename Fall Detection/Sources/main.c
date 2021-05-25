#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>
#include <stdlib.h>

#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"

void MSDelay(unsigned int);


void main(void) {

  AccelRaw read_accel;
  AccelScaled scaled_accel;
  volatile int count = 0;   
  volatile int alert = 0;
  volatile float prev_z =0;

   
    
  int error_code = NO_ERROR;
  unsigned char buffer[128];
  
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
  COPCTL = 7;

  for(;;) {
     
  
    // read the raw values
 
    getRawDataAccel(&read_accel);
    
    // convert the acceleration to a scaled value
    convertUnits(&read_accel, &scaled_accel);    
    
    
    if(abs(scaled_accel.z)>=0.80){
       if(abs(scaled_accel.z)-prev_z>=0.85){
       alert = 1;
       }
       count++;
    }
    
    
    
    prev_z = abs(scaled_accel.z);
    
          
    
    // format the string of the sensor data to go the the serial
    sprintf(buffer, "%.2f, %.2f, %.2f\r\n", scaled_accel.x, scaled_accel.y, scaled_accel.z);
    
    
    
    // output the data to serial
    SCI1_OutString(buffer);
    
    if(alert==1&&count>=5){
      sprintf(buffer, "EMERGENCY!");
      SCI1_OutString(buffer);
    
    }
    
    MSDelay(100);
    _FEED_COP(); /* feeds the dog */
  }/* loop forever */
  
  /* please make sure that you never leave main */
}

void MSDelay(unsigned int itime)
{
   unsigned int i; unsigned int j;
   for(i=0;i<itime;i++)
     for(j=0;j<4000;j++);
}  
