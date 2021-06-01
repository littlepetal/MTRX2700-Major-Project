#include <hidef.h>      /* common defines and macros */
#include <string.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "oc5_isr.h"
#include "delay.h"
#include "voice.h"
  

void main(void){
    
  InitSpeaker();

  while(1)
  {  
  voice(4,0);//voice(distance, condition of fall down)
  }
  
	EnableInterrupts;
	

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
