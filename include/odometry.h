#pragma once
#include "vex.h"



// Thanks to 5225A for odom article and code


struct sPos{
  double x;
  double y;
  double a;
  double leftLst;
  double rightLst;
  double backLst;
};
/**
 * This is the global instance of our odometrey array
 * it's size of 3 because it contains the x,y, and theta returned by our odometry
 * we use this for using odom values throughout our code
 */

extern sPos gPos;

/**
 * Position tracking function
 * using a concept called odometrey we are able to keep track of our global position of the robot instead of a relative position
 * this is useful because we can automatically correct for our error during our movements
 */
int trackPosition();




#define WHEEL_DIAMETER 2.75

// The distance between the tracking wheels and the centre of the robot in inches
#define L_DISTANCE_IN 6.1675
#define R_DISTANCE_IN 6.1675
#define B_DISTANCE_IN 6.8075

// The number of ticks per rotation of the tracking wheel
#define TICKS_PER_ROTATION 360.0

// Used internally by trackPosition. this is the amount the wheel has spun in encoder ticks every loop (we use circumfurence)
#define SPIN_TO_IN_LR (WHEEL_DIAMETER * M_PI / TICKS_PER_ROTATION)
#define SPIN_TO_IN_B (WHEEL_DIAMETER * M_PI / TICKS_PER_ROTATION)

/** 
 * enum positionVals
 * Stores odometry values for indexing our ODOM_ARRAY
 */

enum positionVals
{
	ODOM_X,
	ODOM_Y,
	ODOM_THETA,
};


/**
 * sets a desired odometry pose
 * @param x desired X
 * @param y desired Y
 * @param a desired Theta
 */
void setOdomOrigin(double x, double y, double a,sPos& position);

