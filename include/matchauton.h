#pragma once

#include "vex.h"
#include "odometry.h"

/// autonmous function used in callback
void autonomous();

/// red alliance auton
void red_auton();

/// blue alliance auton
void blue_auton();

/// auton skills run 
void run_auton_skills();

/// simple auton
void middle_goal_dump();

/// task to unlock robot from start
int unlock_robot_task();

/// keeping track of locked status
extern bool unlocked;
extern task blue_intakes; 
extern  task blue_indexer;
extern  task blue_flywheel;

extern task red_intakes;
extern task red_indexer;
extern task red_flywheel;