# psychic-octo-waffle
Group 2 Tuesday 2pm-5pm Lab2

# White cane and guide dog, physical and emotional support package
## Why visually impaired people need our product
#### Physical support
- Visually impaired people requires support to avoid walking into obstacles in daily life. Our device provides a simple obstacle detection system which alerts the user of front on obstacles within 5 metres of contact, with gradually more intense warning sounds as the obstacle becomes closer.
- Our device is superior to other devices on the market because it is fast as it only detects front on obstacles. The user can simply rotate their neck to find a path around the obstacle.
- Our device includes a gyro and servo system which keeps the detector horizontal to the floor and up right at all times, so the user does not need to worry about keeping a tall neck for accurate detection.
- Our device includes an accelerometre fall detection system which can be used to dial an emergency contact if the person has fallen. This emergency dial can be turned off manually by the user if need be.
- A fall also triggers a guide dog whimpering sound which alerts bystanders and urges them to assist the user. 

#### Emotional support
- Not only does our device offer physical support, it offers a personalisable emotional support system.
- We have included a sample 'whimperingpup.mp3' file in the PC interface module to be played to alert bystanders of falls. However, this is easily reconfigurable to play any mp3 file under custom conditions.
- For example, the loss of a guide dog is a cause of immense grief. Sometimes, one would like to be reminded of their past memories with their guide dog, perhaps by a recording of the sound of their paws running towards them, or the playful barks they used to make. 
- These recordings can be played under any prompt configured in the PC interface module by the user.

## Lidar Module (Obstacle detection)

#### Dependencies
- The lidar module will take a PWM signal as input and calculate the distance away (in metres) from the closest obstacle in the direction the lidar is pointing. The distance is returned as a volatile unsigned int.
- The lidar module can be used in conjunction with the microcontroller speaker module to make warning sounds when an obstacle is very close.
- The lidar module can be used in conjunction with the PC interface module to make guide dog sounds when the person has fallen over.
- The lidar module can be used in conjunction with the accelerometre module to run obstacle detection and fall detection together.
- The lidar module can be used in conjunction with the serialisation module to continuously print the value of the currently measured distance in a terminal like PuTTY. 

#### Usability
- First, the user must use `Init_lidar` so that the variables, interrupts and ports used by the lidar module are initialised and configured as intended, which is:
  - `PORT T` as input
  - Enabled timer overflow interrupt
  - Disabled timer fast flag clear all bits
  - Timer prescaler value of 128
  - Enabled timer channel 1 interrupt
  - Timer channel 1 set to inpust capture on both falling and rising edge
  - Initialising variabled used in the lidar module as zero 

#### Functionality
- Once configured, the lidar module is only responsible for returning the distance to the closest obstacle from the lidar in metres as a volatile unsigned int. The function that returns this value is `get_metres()`

## Servo Module

#### Dependencies
-This is a modular function and can be used in conjuction with any module based on the use and it is independent of other modules

#### Usability
- include the servo.h header in the main function
- use `tilt_servo(degrees)` for the tilt motor
- use `rotate_servo(degrees)` for the rotate motor 

#### Functionality
- This module has two functions for the tilt and rotaion respectively, and inputting the degrees will rotate the servo accordingly

#### Testing Procedure
- a serial interface was set up to enter the value for duty cycle of the PWM
- The PWM wave was analysed using the oscilloscop provided in the lab
- The orientation of the servo was checked based on the values given to get calibration



## Speaker Module

#### Dependencies
- This module is used in conjunction with the lidar module to activate the corresponding audio according to the change of the distance parameter.
- This module is used in conjunction with the acceleration module, and is judging whether the user has fallen and continuously warns.
- Used in conjunction with the interface module, it can send signals to other devices at the same time to achieve more functions, such as notifying family members when it falls on the ground.

#### Usability
- Users can customize the audio in the module.
- You can adapt the use of other modules by changing the conditions in the logic judgment.
#### Functionality
- The OC5 module uses an integer parameter to indicate the number of clock cycles that the program should delay, and updates the pin TC5 to trigger the interrupt again in the program. This interrupt will also cause the PT5 pin to turn on and off, which will cause the speaker to vibrate and generate sound waves.
- After configuration, the input value will be judged according to the preset conditions, and the corresponding sound will be played.

## Serialisation Module

#### Dependencies
- The serialisation module would take information from one module and would output information into a terminal where it would be displayed
- The serialisation module would work in conjunction with lidar, accelerometer and gyro as it would be displaying relevant measurements into the terminal
- The serialisation module would work in conjunction with the speaker to produce the right sound effect 

#### Usability
- First the functions are initialised so that the messages are being sent across from the modules
- message is being typed across the board -> output message should be received
- measurements are also displayed onto a terminal

#### Functionality


## Fall detection/Orientation Module

#### Dependencies
- The Fall detection module can be used in conjunction with the PC interface module to make guide dog sounds when the person has fallen over.
- The Fall detection module utilises the MEMS board attached on the PTU to detect the orientation.
- - The Fall detection module can be utilised with the PC interface module to notify an emergency


#### Usability
-  To use this module two variables for current and previous outputs of struct type `fall_output`, which is a specific struct create for this function, should be created.
-  The structs are intialised using `init_fall_output(fall_output input)` function
-  In the main loop of the program, the function fall_detect(prev_output) is called passing the previous output as input.
-  The output of the function `fall_detect(prev_output)` is stored as the current_output
-  The variable emergecny in the current_output struct notifies if the person has fallen down.
-  This module also outputs the acceleration of the object which can be accesed from the outputted struct of `fall_detect()`;

#### Functionality
-  This function has a versatile functionality
-  It can detect if the person has fallen down or not, which is outputted by the varaible `emergency` in the output struct
-  It can output the accelerations in x,y,z axes throug the struct `AccelScaled` in the output struct
-  It can also give a count of how long since the object/person has fallen down from `output`


#### Testing Procedure
- The acceleration values were printed on the serial monitor
- The hardware was oriented in realtime while outputting on the serial, to get the calibration
- Different error conditions were set to check for connection negligence

## PC interface Module

#### Dependencies
- The PC interface module will take a comma deliminated string as input and output a plot of the obstacle distances detected by the lidar and play a guide dog whimpering sound when the accelerometre detects a fall 

#### Usability
- To use this module, the user will need to run a CodeWarrior program with the serialisation, lidar and accelerometres modules. 
- The user must initialise a variable using `unsigned char buffer[12];`, then use `SCI1_Init(BAUD_9600);` and then output the desired values calculated from the lidar and accelerometre modules to serial using `SCI1_OutString(buffer);`
- Once the microcontroller program is configured and running, the user must open `matt.m` and click run.

#### Functionality
- The PC interface is only responsible for plotting in real time and playing the `whimperingpup.mp3` file depending on conditions.

