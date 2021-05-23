#include <hidef.h>      /* common defines and macros */
#include <string.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "oc5_isr.h"
#include "delay.h"

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

                                  


// Define structure //
struct Speaker {
  volatile unsigned int score[200]; 
  volatile unsigned int dur[200];
};


struct Speaker Voice1 = 
{
      {E1, 1, E1, 1, E1, 1, E1, 1},
      {12, 3, 12, 3, 12, 3, 12, 3}
};

struct Speaker Voice2 = 
{
      {1, D2, 1, D2, 1, D2, 1, D2, 1},
      {2, 8, 2, 8, 2, 8, 2, 8, 2}
};
      
      
struct Speaker Voice3 = 
{
      {C3, 1, C3, 1, C3, 1, C3, 1},
      {6, 2, 6, 2, 6, 2, 6, 2}
};
      
      
struct Speaker Voice4 = 
{
      {B4, 1, B4, 1, B4, 1, B4, 1},
      {4, 1, 4, 1, 4, 1, 4, 1}
};
      

struct Speaker Voice5 = 
{
      {A5, 1, A5, 1, A5, 1, A5, 1},
      {3, 1, 3, 1, 3, 1, 3, 1}
};


struct Speaker VoiceFollow = 
{
      {A5, D2, A5, D2, A5, D2, A5, D2},
      {3, 2, 3, 2, 3, 2, 3, 2}
};
      
struct Speaker Voice;  

void main(void) {
  /* put your own code here */
  int j,voiceNumber;
  
  TCTL1 = 0x04; // sets 0C5 to toggle. When event occurs, will toggle PT5
  TIOS  = 0x20; // Selecting channel 5 as output compare
  TSCR1 = 0x90; // Enables timer. 0x90 would mean flag doesn't need to be reset
  TSCR2 = 0x07; // Sets prescaler division to 128. 187500Hz. T = 5.33us
  TIE   = 0x20; // Sets interrupt caused by OC5
  
  // Configure LEDS for debugging //
  DDRB = 0xFF;
  DDRP = 0xFF;
  DDRJ = 0xFF;
  PTP  = 0x00;
  PTJ   = 0x00;
  PORTB = 0x00;
  
  DDRT  = 0x20; // Sets PT5 to be output to speaker
  
  dlycnt = HiFreq; // set delay count for a high pitch
  
  
  voiceNumber = 2;
  
  
  if(voiceNumber <= 1){
    Voice = Voice1;
  }
  else if(voiceNumber <= 2){
    Voice = Voice2;
  }
  else if(voiceNumber <= 3){
    Voice = Voice3;
  }
  else if(voiceNumber <= 4){
    Voice = Voice4;
  }
  else if(voiceNumber <= 5){
    Voice = VoiceFollow;
  }
  else{
    Voice = Voice5;
  }
 
 
 
  // Move data from array to structure //
  // Find number of notes in song (excluding rests) //
  j = 0;
  length = 0;
  while(1) {
    if (Voice.score[j] == 0) {
      break;
    } else if (Voice.score[j] == 2) {
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
    delayby10ms(Voice.dur[j]);
    
    
    // Count notes remaining //
    if (Voice.score[j] != 2) {
      notes_left--;
    }
    
    j++;
    
  }
  
  // After tune is finished disable interrupt and loop forever //
  TIOS &= 0xBF; // Disable 0C5;

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
