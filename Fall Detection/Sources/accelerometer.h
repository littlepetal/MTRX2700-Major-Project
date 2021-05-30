#ifndef ACCELEROMETER_HEADER
#define ACCELEROMETER_HEADER


// data structures containing the raw values
typedef struct AccelRaw {
  int x;
  int y;
  int z;
} AccelRaw;


// data structures containing the raw values
typedef struct AccelScaled {
  float x;
  float y;
  float z;
} AccelScaled;

typedef struct fall_output {
  int   alert;
  int   count;
  int   emergency;
  AccelScaled prev_output;
} fall_output;

void convertUnits(AccelRaw *raw_data, AccelScaled *scaled_data);
void MSDelay(unsigned int);
fall_output init_fall_output(fall_output input_struct);
int is_standing(AccelScaled accel_measurement);
int has_fallen(AccelScaled current_measurement,AccelScaled prev_measurement);
fall_output fall_detect(fall_output prev_output);

#endif