# psychic-octo-waffle
Group 2 Tuesday 2pm-5pm Lab2

# White cane and guide dog replacement package

## Lidar Module

#### Dependencies
- The lidar module will take a PWM signal as input and calculate the distance away (in metres) from the closest obstacle in the direction the lidar is pointing. The distance returned has volatile unsigned int data type.
- The lidar module can be used in conjunction with the speaker module to make warning sounds when an obstacle is very close.
- The lidar module can be used in conjunction with the serialisation module to continuously print the value of the currently measured distance in a terminal like PuTTY. 

#### Usability
- First, the user must use 'Init_lidar' so that the variables, interrupts and ports used by the lidar module are initialised and configured as intended
-   

#### Functionality


## Accelerometre Module

#### Dependencies

#### Usability

#### Functionality


## Gyro Module

#### Dependencies

#### Usability

#### Functionality


## Speaker Module

#### Dependencies
- This module is used in conjunction with the lidar module to activate the corresponding audio according to the change of the distance parameter.
- This module is used in conjunction with the acceleration module and the gyroscope module, and it will continue to warn the user when it is judged that the user is down.

#### Usability
- Users can customize the audio in the module.
- You can adapt the use of other modules by changing the conditions in the logic judgment.
#### Functionality


## Serialisation Module

#### Dependencies
- The serialisation module would take information from one module and would output information into a terminal where it would be displayed
- The serialisation module would work in conjunction with lidar, accelerometer and gyro as it would be displaying relevant measurements into the terminal
- The serialisation module would work in conjunction with the speaker to produce the right sound effect 

#### Usability
- First the functions are initialised so that the messages are being sent across from the modules
- message is being typed across the board -> output message should be received
- measurements should be displayed on a terminal
- 


#### Functionality


## Obstacle detection Module

#### Dependencies

#### Usability

#### Functionality


## Fall detection Module

#### Dependencies

#### Usability

#### Functionality
