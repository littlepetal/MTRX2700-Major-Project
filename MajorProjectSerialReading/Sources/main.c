#include <hidef.h>            /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include <math.h>
#include <stdio.h>


// struct would allows us to define what type of data is required.
typedef struct {
  int var_1;
  float var_2;
  char string_data[24];
} data_to_serialise;

void main(void) {

  // a data struct that we would like to serialise and send to another computer/device/file/etc
  data_to_serialise data_to_send, data_to_receive, data_example;

  // a buffer used to transmit the serialised message  
  unsigned char transmit_buffer[sizeof(data_to_serialise)];
  unsigned char *transmit_buffer_ptr = &transmit_buffer;
  
  data_to_send.var_1 = 12;
  data_to_send.var_2 = 4.231;
  data_example.var_1 = 26;
  data_example.var_2 = 3.24;
  
  sprintf(&data_to_send.string_data[0], "serial number %d", data_to_send.var_1);
  sprintf(&data_example.string_data[0], "serial number %d", data_example.var_1);

  // store the struct in the buffer
  memcpy(transmit_buffer_ptr, (unsigned char*)(&data_to_send), sizeof(data_to_serialise));
                                         
  // load the value from the buffer (presume that you have just received this from the 
  //  serial/network/file/etc and that we know the data contains the struct we are looking for
  memcpy((unsigned char*)(&data_to_receive), transmit_buffer_ptr, sizeof(data_to_serialise));  
  
  // display the data being received - data in the buffer 
  sprintf(&data_to_receive.string_data[0], "serial number %d", data_to_receive.var_1);
  
  EnableInterrupts;
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
