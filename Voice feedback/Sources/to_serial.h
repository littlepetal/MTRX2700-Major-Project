// Serial header //
#ifndef SCI1_H
#define SCI1_H

// Function configures SCI1 port for transmissions only //
void SCI1_config(void);


// Function outputs to serial result //
void result_to_serial(double time);


// INTERRUPT //
// Main function is to send a string to serial //
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void SCI1_T_ISR(void);


#endif