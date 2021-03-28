#include "matchauton.h"


void run_auton_skills() {
  moveToPointAndAngle(10, 14, 45);


  // deploying robot
  task deployTask = task( unlock_robot_task );
  do {
    task::sleep(5);
  }while(!unlocked);
  deployTask.stop();

  // start subsystem tasks
  task matchIntakes = task( intakeTask );
  task matchIndexer = task( indexerTask );
  task matchFlywheel = task( flywheelTask );


  //score in goal 1
  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;
  
  moveToPointAndAngle(10, 20, 45);
  STOP_INDEXERS_BOTTOM_DETECTED = true;
  task::sleep(200);
  moveToPointAndAngle(39, 23, 90);
  task::sleep(550);

  //moving to goal 2
  STOP_INTAKES = false;
  STOP_INDEXERS_BOTTOM_DETECTED = false;
  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;

  moveToPointAndAngle(39, 23, 90);
  
  task::sleep(100);

  RUN_INTAKES = false;
  // INTAKE_OUT = false;
  STOP_INTAKES = true;

  turnToDegree(-50.0_deg);

  moveToPointAndAngle(39, 23, 90); 
  RUN_INDEXERS = false;
  STOP_INDEXERS = true;
  
  task::sleep(100);

}