#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void MSDelay(unsigned int itime);

void tilt_servo(unsigned int degrees);
void rotate_servo(unsigned int degrees);

void tilt_servo(unsigned int degrees){
  int duty = (degrees/5);
  
  /* put your own code here */
  PWMPRCLK=0x03;        //ClockA=Fbus/2**4=24MHz/8=3MHz	
	PWMSCLA=125; 	        //ClockSA=3MHz/2x150=10,000Hz
	PWMCLK=0x20 ; 	  //ClockSB for chan 7
	PWMPOL=0x20; 		      //high then low for polarity
	PWMCAE=0x0; 		      //left aligned
	PWMCTL=0x04;	          //8-bit chan, PWM during freeze and wait
	PWMPER5=200; 	        //PWM_Freq=ClockSB/200=10000Hz/200=50Hz. 
	PWMDTY5 = duty; //duty cycle = duty/period x 100%    
  PWMCNT5= duty;	//clear initial counter. This is optional
  PWME = 0x20; 	    //Enable chan 7 PWM
  MSDelay(100);
  
}

void rotate_servo(unsigned int degrees){

  int duty = 7+(degrees/9);
  
  /* put your own code here */
  PWMPRCLK=0x30;        //ClockB=Fbus/2**4=24MHz/8=3MHz	
	PWMSCLB=125; 	        //ClockSB=3MHz/2x150=10,000Hz
	PWMCLK= 0x80 ; 	  //ClockSB for chan 7
	PWMPOL=0x80; 		      //high then low for polarity
	PWMCAE=0x0; 		      //left aligned
	PWMCTL=0x04;	          //8-bit chan, PWM during freeze and wait
	PWMPER7=200; 	        //PWM_Freq=ClockSB/200=10000Hz/200=50Hz. 
  PWMDTY7 = duty; //duty cycle = duty/period x 100%    
	PWMCNT7= duty;	//clear initial counter. This is optional
  PWME = 0x80; 	    //Enable chan 7 PWM
  MSDelay(100);
}


void main(void) {



  int degree1 = 180;
  int degree2 = 0 ;
  

   
   
  for(;;) {
      
      
      tilt_servo(degree1);
      
      MSDelay(500);
      rotate_servo(0);
      degree1 = degree1-30;
      degree2 = degree2+30;
      if(degree1<=0){
        degree1 = 180;
      }
      if(degree2>=180){
        degree2 = 0;
      }
      
      
     
    //_FEED_COP(); /* feeds the dog */
   }
}


void MSDelay(unsigned int itime)
{
   unsigned int i; unsigned int j;
   for(i=0;i<itime;i++)
     for(j=0;j<4000;j++);
}