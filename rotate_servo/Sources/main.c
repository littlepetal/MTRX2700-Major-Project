#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



void main(void) {
  /* put your own code here */
  
  PWMCLK = 0x20;
  PWMPOL = 0x21;
  PWMCTL = 0X22;
  PWMCAE = 0X33;
  PWMPRCLK = 0X22;
  PWMPER0 =  72;
  PWMDTY0 =  20;
	EnableInterrupts;
	
	


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
