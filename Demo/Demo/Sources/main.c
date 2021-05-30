#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "timers.h"
#include "lidar.h"
#include "simple_serial.h"
#include "iic.h"





volatile int dlycnt; // Delay count for 0C5
volatile int length; // Length of music score, number of notes.
volatile int notes_left;
                                         
                                         
#define HiFreq  0x5D
#define LoFreq  0xBB 

#define   E1 500
#define   D2 400
#define   C3 300
#define   B4 200
#define   A5 100

                                  


// Define structure of voice//

struct Speaker {
  volatile unsigned int score[500]; 
  volatile unsigned int dur[500];
};


struct Speaker Voice1 = 
{
      {E1, 1, E1, 1},
      {12, 6, 12, 5}
};

struct Speaker Voice2 = 
{
      {D2, 1, D2, 1, D2, 1},
      {8, 4, 8, 4, 8, 3}
};
      
      
struct Speaker Voice3 = 
{
      {C3, 1, C3, 1, C3, 1, C3, 1},
      {6, 3, 6, 3, 6, 3, 6, 2}
};
      
      
struct Speaker Voice4 = 
{
      {B4, 1, B4, 1, B4, 1, B4, 1, B4, 1, B4, 1},
      {4, 2, 4, 2, 4, 2, 4, 2, 4, 1, 4, 1}
};
      

struct Speaker Voice5 = 
{
      {A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1},
      {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
};


struct Speaker VoiceFall = 
{
      {A5, D2, A5, D2, A5, D2, A5, D2},
      {3, 2, 3, 2, 3, 2, 3, 2}
};
      
struct Speaker Voice;  











void main(void) {




  /* put your own code here */
  
  

  
  //keep active alarm after fall down once//
  /*while(acceleration >= 1)
  {
    fallDown = 0;
  }   */
  
  
  /*
  
  //voice conditions//
  if(fallDown == 0 && voiceNumber == 1){
    Voice = Voice1;
    toSerial = 1;
  }
  else if(fallDown == 0 && voiceNumber == 2){
    Voice = Voice2;
    toSerial = 2;
  }
  else if(fallDown == 0 && voiceNumber == 3){
    Voice = Voice3;
    toSerial = 3;
  }
  else if(fallDown == 0 && voiceNumber == 4){
    Voice = Voice4;
    toSerial = 4;
  }
  else if(fallDown == 0 && voiceNumber == 5){
    Voice = Voice5;
    toSerial = 5;
  } 
  else{
    Voice = VoiceFall;
    toSerial = 6;
  }
  
  
  
  

  // Move data from array to structure //
  // Find number of notes in song (excluding rests) //
  j = 0;
  length = 0;
  while(1) {
    
    if (Voice.score[j] == 0) {
      break;
    } else if (Voice.score[j] == 1) {
      // Do nothing //
      j++;
    } else {
      // If a note //
      length++;
      j++;
    }
  }
  
  // Set notes left equal to length //
  notes_left = length;
  
  
  TC5 = TCNT + HiFreq;

	EnableInterrupts;
	

  j = 0;
  while(1) {
    if (Voice.score[j] == 0) {
      return;
    }
    dlycnt = Voice.score[j];
    delay(Voice.dur[j]);
    
    
    // Count notes remaining //
    if (Voice.score[j] != 1) {
      notes_left--;
    }
    
    j++;
    
  }
  
  // After tune is finished disable interrupt and loop forever //
  TIOS &= 0xBF; // Disable 0C5;


  */











  volatile unsigned int distance = 0;
  //volatile unsigned int fall = 0;
  //int j,voiceNumber,fallDown,acceleration,toSerial;
  
  unsigned char buffer[12];       // buffer for serial output
  
  
  /*
  TCTL1 = 0x04; // sets 0C5 to toggle. When event occurs, will toggle PT5
  TIOS  = 0x20; // Selecting channel 5 as output compare
  TSCR1 = 0x90; // Enables timer. 0x90 would mean flag doesn't need to be reset
  TSCR2 = 0x07; // Sets prescaler division to 128. 187500Hz. T = 5.33us
  TIE   = 0x20; // Sets interrupt caused by oc5

  
  DDRT  = 0x20; // Sets PT5 to be output to speaker
  
  dlycnt = HiFreq; // set delay count for a high pitch
 
 
  acceleration = 0;
  fallDown = 1;
  voiceNumber = 3;      */
  
  
  
  
  
  // initialises the lidar
  Init_Lidar();
  
  // initialise serial interface  
  SCI1_Init(BAUD_9600); 


	EnableInterrupts;


  for(;;) {
  
    // calculate the distance from the lidar to the closest obstacle
    //enable_lidar_interrupts();
    distance = get_metres();
    //disable_lidar_interrupts();
   
       
    //fall = fallDetect();
    
    // serial output distance in metres
    sprintf(buffer,"%u\r\n",distance);
    SCI1_OutString(buffer);
    
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
