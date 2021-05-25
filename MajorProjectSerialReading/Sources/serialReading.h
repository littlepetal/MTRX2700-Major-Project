#ifndef TIMERS_HEADER
#define TIMERS_HEADER

//defining a structure for the serial, what has to be defined
//here: 
/*typedef struct{



}SerialPort*/

// struct would allows us to define what type of data is required.
typedef struct {
  int var_1;
  double var_2;
  char string_data_1[30];
  char string_data_2[30];
  char output_string[30];
} data_to_serialise;

//function to initialise serial
void Init_sci(void);

//serial interrupt definiton
__interrupt void RE_ISR(void);

#endif