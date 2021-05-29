// Send serial implementation //
#include "derivative.h"
#include "serial.h"
#include "time.h"
#include "table.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

// Variables //
extern volatile char buff[30]; // String to output to serial //
extern volatile int transmission_flag;
extern volatile int buff_length;
extern volatile int transmit_count;
extern volatile int table_row;



// Function takes a number, converts it to a string and then outputs the result to SCI1 //
void SCI1_config(void){
  SCI1BDH = 0x00;
  SCI1BDL = 0x9C; // Baud Rate 9600
  SCI1CR1 = 0x4C; // 8 bit word length
  SCI1CR2 = 0x08; // Enable transmissions but not allowing interrupts yet, 0x88 for interrupts enabled //
  return;
}


// Function to write result to serial //
void result_to_serial(double time) {
  int i;
  
  // Initialises table for this result //
  table_body();

  // Convert to a string //
  sprintf(buff, "%11.8lf", time);
  
  // Length of string //
  for (i = 0; i < 100; i++) {
    if (buff[i] != '\0') {
      buff_length++;
    } else {
      break;
    }
  }
  
  // Send string to serial //
  // Keep everything here while serial is running //
  // Right now this is without using interrupts, very simple polling to do it //
  transmission_flag = 0;
  while(transmission_flag == 0) {

    if ((SCI1SR1 & SCI1SR1_TDRE_MASK) != 0) {
      SCI1DRL = buff[transmit_count];
      transmit_count++;
    } else if (transmit_count == buff_length) {
      SCI1DRL = 0x0D;  // NEW LINE //
      break;
    }
  }
  
  // Reset variables
  transmit_count = 0;
  buff_length = 0;
  table_row++;
  TSCR1 = 0x80; // RESUME TIMER //
  
  // Return to main //
  return;
}


// -------------------------- INTERRUPT FOR SCI1 ------------------------------------------------------ //


#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void SCI1_T_ISR(void) {
  // If shift register is empty and ready for next character //
  if ((SCI1SR1 & SCI1SR1_TDRE_MASK) != 0) {
    
      // Check if transmit length matches the input string //
      if (transmit_count == buff_length) {
        transmission_flag = 1;
        transmit_count = 0; // reset counter and flag
        
        SCI1CR2 = 0x08; // Disable transmission interrupts //
        return;
      }
                                              
      SCI1DRL = buff[transmit_count];
    }
    
    // If all good go to next character //
    transmit_count++;
    
    return;
}
    
  