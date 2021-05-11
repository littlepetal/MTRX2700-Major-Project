#ifndef TIMERS_HEADER
#define TIMERS_HEADER

//defining a structure for the serial, what has to be defined
//here: 
/*typedef struct{



}SerialPort*/


//function to initialise serial
void Init_sci(void);

//serial interrupt definiton
__interrupt void RE_ISR(void);

#endif