#pragma once
#include "vex.h"

/// Intake subsystem task that runs in auton
int intakeTask();

/// Indexer subsystem task that runs in auton
int indexerTask();

/// Fluwheel subsystem task that runs in auton
int flywheelTask();

extern bool RUN_INTAKES; // run intakes at full speed
extern bool STOP_INTAKES; // stop intakes
extern bool STOP_FLYWHEEL; //stop scorer
extern bool SCORE; //score a ball into a goal
extern bool SCORE2; // score 2 balls into goal
extern bool STOP_FLYWHEEL_TOP_DETECTED; // index a ball to the flywheel and stop when the top line sensor detcts a ball
extern bool RUN_FLYWHEEL; // run scorer at max speed 
extern bool RUN_INDEXERS; // run indexers at max speed
extern bool STOP_INDEXERS; //stop indexers
extern bool STOP_INDEXERS_BOTTOM_DETECTED; //index a ball to the indexer and stop the indexer when the bottom line sensor detects a ball
extern bool INTAKE_OUT; // reverse intakes
