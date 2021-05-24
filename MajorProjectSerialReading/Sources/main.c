#include <hidef.h>            /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include <math.h>
#include <stdio.h>


// struct would allows us to define what type of data is required.
typedef struct {
  int var_1;
  double var_2;
  char string_data_1[30];
  char string_data_2[30];
  char output_string[30];
} data_to_serialise;

void main(void) {

  // a data struct that we would like to serialise and send to another computer/device/file/etc
  data_to_serialise data_to_send, data_to_receive;

  // a buffer used to transmit the serialised message  
  unsigned char transmit_buffer[sizeof(data_to_serialise)];
  unsigned char *transmit_buffer_ptr = &transmit_buffer;
  
  data_to_send.var_1 = 12;
  data_to_send.var_2 = 4.231;


  sprintf(&data_to_send.string_data_1[0], "serial number %d", data_to_send.var_1);
  sprintf(&data_to_send.string_data_2[0], "serial number %lf", data_to_send.var_2);
  sprintf(&data_to_send.output_string[0], "the output string is hello");
  
  // store the struct in the buffer
  memcpy(transmit_buffer_ptr, (unsigned char*)(&data_to_send), sizeof(data_to_serialise));
                                         
  // load the value from the buffer (presume that you have just received this from the 
  //  serial/network/file/etc and that we know the data contains the struct we are looking for
  memcpy((unsigned char*)(&data_to_receive), transmit_buffer_ptr, sizeof(data_to_serialise));  
  
  
  // display the data being received - data in the buffer
   
  //sprintf(&data_to_receive.string_data_1[0], "serial number %d", data_to_receive.var_1);
  //sprintf(&data_to_receive.string_data_2[0], "serial number %lf", data_to_receive.var_2);
  
  
  /* Need place to clear memory from stack - stack size increase  */                                      
  
  EnableInterrupts;
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
