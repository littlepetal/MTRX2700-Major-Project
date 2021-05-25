#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timers.h"



void main(void) {
  /* put your own code here */
    
  Init_TOF();
  //Init_TC2();
  Init_TC1();
  
  // Init_PTH();
  
  //DDRH = 0xFF;
  
  DDRT = 0x00;
  
  reset_overflow_count();
  reset_edges_count();
  reset_start_count();
  reset_end_count();
  reset_metres();

	EnableInterrupts;
	
	
	// trigger
	//PTH = 0x00;
	
  
	


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
