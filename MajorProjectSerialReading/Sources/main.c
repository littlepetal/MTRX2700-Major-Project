#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <hidef.h>            /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "sci1.h"
#include "serialReading.h"


void main(void) {

  /* Method 1: Basic one (just printing information onto strings as output)*/
  
  // a data struct that we would like to serialise and send to another computer/device/file/etc
  data_to_serialise data_to_send, data_to_receive;

  // a buffer used to transmit the serialised message (this is the intermediate stage)  
  unsigned char transmit_buffer[sizeof(data_to_serialise)];
  unsigned char *transmit_buffer_ptr = &transmit_buffer;
  
  data_to_send.var_1 = 12;
  data_to_send.var_2 = 4.231;

  // Issue so far if set string, no problems
  sprintf(&data_to_send.string_data_1[0], "serial number %d", data_to_send.var_1);
  sprintf(&data_to_send.string_data_2[0], "serial number %lf", data_to_send.var_2);
  sprintf(&data_to_send.output_string[0], "everything should be alright");
  
  // store the struct in the buffer
  memcpy(transmit_buffer_ptr, (unsigned char*)(&data_to_send), sizeof(data_to_serialise));
                                         
  // load the value from the buffer (presume that you have just received this from the 
  //  serial/network/file/etc and that we know the data contains the struct we are looking for
  memcpy((unsigned char*)(&data_to_receive), transmit_buffer_ptr, sizeof(data_to_serialise));  

  /* Section 2: Using interrupts to print out serial to a terminal (worked if board connected) */
  Init_sci();
  
  
  /* Method 3: Attempting to connect to serial to communicate between other modules */
  
  
  EnableInterrupts;
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
