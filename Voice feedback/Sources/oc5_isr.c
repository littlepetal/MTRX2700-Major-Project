#include "derivative.h"
#include "oc5_isr.h"

extern volatile int dlycnt;

// OC5 ISR //
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void OC5_ISR(void)  {
  
  // Pops interrupt once TCNT reaches this place
  //if (PTT == 0x20){
    //PTT = 0x00;
  //} else {
    //PTT = 0x20;
  //}
  
  TC5 += dlycnt;
  
  return; // return from interrupt
}