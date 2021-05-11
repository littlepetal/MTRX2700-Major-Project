#include "serialReading.h"
#include <stdio.h>

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */

char re[100];
volatile int re_place;
unsigned char SCIString[12];

// Function to initialise serial reading and transmitting
void Init_sci(void){
  
  SCI0BDH = 0x00;             // Set the baud rate at 9600
  SCI0BDL = 156; 
  SCI0CR2 = 0x2c; //re te and rtede
  //SCI1CR2 = 0x8c; //re te and rtde
  
  re_place = 0;
  SCI0CR2 |= 0x20; //enable to rdte intterupt  
}

// Initialise serial interrupt
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void RE_ISR(void){

  
    // Message being received from serial to board
    if(SCI0SR1 & 0x20 && SCI0CR2 & 0x20){ /*If reception flag is set*/
    SCI0SR1;
      
      if(SCI0DRL != 13){                /*character ret */
        SCIString[re_place] = SCI0DRL;
       re_place = re_place +1;
      }
      
      else{
        SCIString[re_place] = 10;
        re_place = re_place +1;
        SCIString[re_place] = 13;
        re_place = 0; 
        SCI0CR2 |= 0x80; //enable tranmit interupt
      }
   }
  
  // Message being transmitted from board to serial
  if (SCI0SR1 & 0x80 && SCI0CR2 & 0x80 ){ /*If transmission flag is set*/
    SCI0SR1;
    if(SCIString[re_place] != 13 ){
      SCI0DRL = SCIString[re_place];
      re_place = re_place +1;
    }
    else{
    SCI0DRL = 13;
    re_place = 0;
    SCI0CR2 &= 0x7F; /*Disable TDRE interrupt*/
    //SCI1CR2 |= 0x10;
    }
  } 
  

  return;
}