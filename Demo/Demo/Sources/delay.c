#include "delay.h"
#include "derivative.h"


// Simple delay function //
void delaySpeaker(int k) {
    char i;
    //TIOS  |=  0x40; // Enable OC6
    TIOS_IOS6 = 1;
    
    TC6   = TCNT + 30000; // Starting OC6 operation with delay
    
    for(i = 0; i<k ;i++) {
      
      while(!(TFLG1 & 0x40));
      TC6 +=  30000;
    }
    
    //TIOS &= 0xBF; // Disable OC6
    TIOS_IOS6 = 1;
}
  