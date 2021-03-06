#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "oc5_isr.h"
#include "delay.h"
#include "simple_serial.h"


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
#define   ZZ 20
                                  


// Define structure of voice//
struct Speaker {
  volatile unsigned int score[300]; 
  volatile unsigned int dur[300];
};


struct Speaker Voice1 = 
{
      //{E1, 1, E1, 1},
      //{12, 6, 12, 5}
      {E1, 1},
      {2, 1}
};

struct Speaker Voice2 = 
{
      //{D2, 1, D2, 1, D2, 1},
      //{8, 4, 8, 4, 8, 3}
      {D2, 1},
      {2, 1}
};
      
      
struct Speaker Voice3 = 
{
      //{C3, 1, C3, 1, C3, 1, C3, 1},
      //{6, 3, 6, 3, 6, 3, 6, 2}
      {C3, 1},
      {2, 1}
};
      
      
struct Speaker Voice4 = 
{
      //{B4, 1, B4, 1, B4, 1, B4, 1, B4, 1, B4, 1},
      //{4, 2, 4, 2, 4, 2, 4, 2, 4, 1, 4, 1}
      {B4, 1},
      {2, 1}
};
      

struct Speaker Voice5 = 
{
      //{A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1, A5, 1},
      //{2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}
      {A5, 1},
      {2, 1}
};

struct Speaker Voice6 = 
{
      {ZZ, ZZ},
      {2, 1}
};

struct Speaker VoiceFall = 
{
      //{A5, D2, A5, D2, A5, D2, A5, D2},
      //{3, 2, 3, 2, 3, 2, 3, 2}
      {A5, D2},
      {2, 1}
};
      
struct Speaker Voice;

void InitSpeaker(void){
  //TCTL1 = 0x04; // sets 0C5 to toggle. When event occurs, will toggle PT5
  TCTL1_OL5 = 1;
  TCTL1_OM5 = 0;
  
  //TIOS  = 0x20; // Selecting channel 5 as output compare
  TIOS_IOS5 = 1;
  
  TSCR1 = 0x80; // Enables timer. 0x90 would mean flag doesn't need to be reset
  TSCR2 = 0x87; // Sets prescaler division to 128. 187500Hz. T = 5.33us
  
  //TIE   = 0x20; // Sets interrupt caused by oc5
  TIE_C5I = 1;
  
  //DDRT  = 0x20; // Sets PT5 to be output to speaker
  DDRT_DDRT5 = 1;
  
  dlycnt = HiFreq; // set delay count for a high pitch
}
    

void voice(int voiceNumber,int fallDown) {
  /* put your own code here */
  
  int j,toSerial;
  unsigned char bufferVoice[12];
 
  //TSCR2 = 0x07;   
  //voice conditions//  
  if(fallDown == 0 && voiceNumber == 4){
    Voice = Voice1;
    toSerial = 1;
  }
  if(fallDown == 0 && voiceNumber == 3){
    Voice = Voice2;
    toSerial = 2;
  }
  if(fallDown == 0 && voiceNumber == 2){
    Voice = Voice3;
    toSerial = 3;
  }
  if(fallDown == 0 && voiceNumber == 1){
    Voice = Voice4;
    toSerial = 4;
  }
  if(fallDown == 0 && voiceNumber == 0){
    Voice = Voice5;
    toSerial = 5;
  } 
  if(fallDown == 0 && voiceNumber > 4){
    Voice = Voice6;
    toSerial = 6;
  }
  if(fallDown == 1){
    Voice = VoiceFall;
    toSerial = 7;
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
  //TFLG1_C5F = 1;
  //TFLG1_C5F = 0;
  
	EnableInterrupts;
	

  j = 0;
  while(1) {
    if (Voice.score[j] == 0) {
      return;
    }
    dlycnt = Voice.score[j];
    delaySpeaker(Voice.dur[j]);
    
    
    // Count notes remaining //
    if (Voice.score[j] != 1) {
      notes_left--;
    }
    
    j++;
    
  }
  

  
  // After tune is finished disable interrupt and loop forever //
  TIOS &= 0xBF; // Disable 0C5;
  return;


  //TSCR2 = 0x87;
  /*
  for(;;) {
  
  sprintf(bufferVoice,"%u\r\n",toSerial);
  SCI1_OutString(bufferVoice);
  
  
    _FEED_COP();
  } 
  */
  
  /* loop forever */
  /* please make sure that you never leave main */
}
