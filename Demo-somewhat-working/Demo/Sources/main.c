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
  
  
  // lidar and acc module WORKING
  /*
  fall_output current_output;
  fall_output prev_output;
  init_fall_output(prev_output);
    
  Init_Lidar();
  Init_TC7();
  */
  
  // speaker module WORKING
  /*
  InitSpeaker();
  */
  
  // lidar module WORKING
  /*
  Init_Lidar();
  */


  // speaker and acc modules MOSTLY WORKING
  /*
  fall_output current_output;
  fall_output prev_output;
  init_fall_output(prev_output);
  Init_TC7();
  
  InitSpeaker();
  */
  
  
  // speaker and lidar module MOSTLY WORKING
   /*
    Init_Lidar();
    InitSpeaker();
   */
   
   
   
  // speaker and lidar and acc module WORKING
  
  fall_output current_output;
  fall_output prev_output;
  init_fall_output(prev_output);
    
  Init_Lidar();
  Init_TC7();
  InitSpeaker();
  
  
   
   
 
  
  // initialise serial interface  
  SCI1_Init(BAUD_9600); 
    
  //COPCTL = 7;

	EnableInterrupts;
	

  for(;;) {
    
    
      // lidar and acc module WORKING
      /*
      // calculate the distance from the lidar to the closest obstacle
      distance = get_metres();
    
      // check whether subject has fallen
      current_output = fall_detect(prev_output);
      prev_output = current_output;
    
      // serial output distance in metres, fall boolean
      sprintf(buffer,"distance: %u, fall: %d\r\n",distance, current_output.emergency);
      SCI1_OutString(buffer); 
      */
    
    
    
    
    // speaker module WORKING
    /*
    voice(4, 1);
    */
    
    
    
      // lidar module WORKING
      /*
      distance = get_metres();
    
      // serial output distance in metres
      sprintf(buffer,"distance: %u\r\n",distance);
      SCI1_OutString(buffer);
      */
       
    
    // speaker and acc modules MOSTLY WORKING
    /*
    current_output = fall_detect(prev_output);
    prev_output = current_output;  
    
    distance = 10;
    voice(distance, current_output.emergency);
    
    sprintf(buffer,"fall: %d\r\n",current_output.emergency);
    SCI1_OutString(buffer);
    */
    
    
    
    // speaker and lidar module MOSTLY WORKING    
    /*  
      // calculate the distance from the lidar to the closest obstacle
      distance = get_metres();
      //distance = 0;
      
      // play warning sounds   
      voice(distance, 0);
      
      // serial output distance in metres
      sprintf(buffer,"distance: %u\r\n",distance);
      SCI1_OutString(buffer);
    */  
    
    
    
    // speaker and lidar and acc module WORKING   
      
      // calculate the distance from the lidar to the closest obstacle
      distance = get_metres();
      //distance = 0;
      
      // check whether subject has fallen
      current_output = fall_detect(prev_output);
      prev_output = current_output;
      
      
      //TSCR1 = 0x90;
      TSCR1_TFFCA = 1;    // enable timer fast flag clear all bits
      
      // play warning sounds   
      voice(distance, current_output.emergency);
      
      //TSCR1 = 0x80;
      TSCR1_TFFCA = 0;   // disable timer fast flag clear all bits
      
      // serial output distance in metres
      sprintf(buffer,"distance: %u, fall: %d\r\n",distance, current_output.emergency);
      SCI1_OutString(buffer);
      

    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
