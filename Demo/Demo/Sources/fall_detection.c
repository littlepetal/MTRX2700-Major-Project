#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>
#include <stdlib.h>

#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"
#include "accelerometer.h"



/*function to detect if the person has fallen down and need for an emergency*/

fall_output fall_detect(fall_output prev_output){
    AccelRaw read_accel;
    AccelScaled scaled_accel;
    fall_output current_output = prev_output;
    
    int error_code = NO_ERROR;
    
    error_code = iicSensorInit();
    
    // read the raw values
 
    getRawDataAccel(&read_accel);
    
    // convert the acceleration to a scaled value
    convertUnits(&read_accel, &scaled_accel);    
    
    
    //checking if there is a sudden change in the acceleration
    if(!is_standing(scaled_accel)){
       current_output.alert = 0;
       
    } else{
       if(has_fallen(scaled_accel,current_output.prev_output)){
       current_output.alert = 1;
       }
       current_output.count++;
    }
    
    
    //loading the previous values for next iteration    
    current_output.prev_output = scaled_accel;
    
    
    //checking if the person has fallen down
    if(current_output.alert==1&&current_output.count>=3){
      current_output.emergency = 1;
         
    } else{
      current_output.emergency = 0;
    }
    
    
    
    MSDelay(100); 
    
    return current_output;
  
}


/*intializing the struct for fall_detect function*/
fall_output init_fall_output(fall_output input_struct){
  input_struct.count = 0;   
  input_struct.alert = 0;
  input_struct.prev_output.z =0;
  input_struct.prev_output.y =0;
  input_struct.emergency =0;
}

/*function to detect if the person is standing*/
int is_standing(AccelScaled accel_measurement){
  int result = 0;
  
  if(abs(accel_measurement.z)<=0.30&&abs(accel_measurement.y)<=0.30){
    result = 0;
  } else if((abs(accel_measurement.z)>=0.75||abs(accel_measurement.y)>=0.75)){
    result = 1;
  }
  return result;
  
}
/*function to detect the fall of the object in z,y-direction*/
int has_fallen(AccelScaled current_measurement,AccelScaled prev_measurement){
  int result = 0;
  if(abs(current_measurement.z)-abs(prev_measurement.z)>=0.65||abs(prev_measurement.z)-abs(current_measurement.z)>=0.65){
    result = 1;
  } else if(abs(current_measurement.y)-abs(prev_measurement.y)>=0.65||abs(prev_measurement.y)-abs(current_measurement.y)>=0.65){
    result = 1;
  } else{
    result = 0;
  }
  return result;

}
/*Delay Function*/
void MSDelay(unsigned int itime)
{
   unsigned int i; unsigned int j;
   for(i=0;i<itime;i++)
     for(j=0;j<4000;j++);
}  



 