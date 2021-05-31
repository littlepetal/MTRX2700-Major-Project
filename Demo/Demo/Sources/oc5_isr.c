#include "derivative.h"
#include "oc5_isr.h"

extern volatile int dlycnt;

// OC5 ISR //
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void OC5_ISR(void)  {
  
  
  TC5 += dlycnt;
  
  TFLG1_C5F = 1;
  //TFLG1_C5F = 0;
  
  return; // return from interrupt
}