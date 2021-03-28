#pragma once
#include "vex.h"


/**
 * turns the robot to a specified angle using the inertial sensor
 * the degree specifed is feild-relative
 * @param degree desired angle to turn to
 */
void turnToDegree(double degree);


/**
 * moves the robot to a desired x, y, and theta
 * Using trignometrey and PID we are able to move our xDrive to a desired postion and heading
 * The explanation of the trig is inside the function defintion in chasssis_function.cpp
 * @param xTarget desired x value to move to
 * @param yTarget desired y value to move to
 * @param angleTarget desired angle value to move to
 */

void moveToPointAndAngle(double target_x, double target_y, double target_theta);


/**
 * Moves the robot side-to-side a given distance and speed
 * We only use this function in match autonomous because it really isnt that consistently precsise and accurate 
 * due to the lack of PID and relative nature of the function
 * but it is good enough for the small distances in match autonomous
 * @param amount desired distance (in inches)
 * @param speed desired speed (between 0-100)
 */
void strafeInch(double distance, double speed);

/**
 * Moves the robot up and down a given distance and speed
 * We only use this function in match autonomous because it really isnt that consistently precsise and accurate 
 * due to the lack of PID and relative nature of the function
 * but it is good enough for the small distances in match autonomous
 * @param amount desired distance (in inches)
 * @param speed desired speed (between 0-100)
 */
void moveInch(double distance, double speed);
void moveInch(double distance, double speed, double time);

/**
 * Main helper function for voltage control of our x drive
 * @param leftFrontVoltage desired voltage for left front motor
 * @param rightFrontVoltage desired voltage for right front motor
 * @param leftBackVoltage desired voltage for left back motor
 * @param rightBackVoltage desired voltage for right back motor
 */
void setDriveVoltage(double leftFrontVoltage, double rightFrontVoltage , double leftBackVoltage, double rightBackVoltage);

/**
 * uses braketype hold to hold the drive motors after movement 
 */
void holdDrive();

/**
 * uses braketype brake to hold the drive motors after movement 
 */
void brakeDrive();

/**
 * Main helper function for velocity control of our x drive
 * @param leftFrontVoltage desired voltage for left front motor
 * @param leftBackVoltagedesired voltage for right front motor
 * @param rightBackVoltage desired voltage for left back motor
 * @param rightFrontVoltage desired voltage for right back motor
 */
void setDriveVelocity( double leftFrontVelocity, double leftBacktVelocity, double rightBacktVelocity, double rightFrontVelocity );


/// Print inertial sensor value to controller screen to make sure it's not drifting too much
int print_inertial_drift_task();