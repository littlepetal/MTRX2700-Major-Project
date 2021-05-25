#include "delay.h"
#include "derivative.h"


// Simple delay function //
void delay(int kk) {
    char ix;
    TIOS  |=  0x40; // Enable OC6
    TC6   = TCNT + 30000; // Starting OC6 operation with 20ms delay
    
    for(ix = 0; ix<kk ;ix++) {
      
      while(!(TFLG1 & 0x40));
      TC6 +=  30000;
    }
    
    TIOS &= 0xBF; // Disable OC6
}
  