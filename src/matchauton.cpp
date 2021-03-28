#include "matchauton.h"
#include "Selector/selectorAPI.h"
#include "Selector/selectorImpl.h"

bool unlocked = false;

int unlockTime = 600;

void autonomous() {
  inert.setRotation(0,degrees);
 //red_auton();
    blue_auton();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
  // if we havent selected skills on the auton selector then we are in match auton


  /*
  if(!selector3142a::skills) {

  
  if(selector3142a::middle_goal_dump) {
    // run simple middle goal dump code
    middle_goal_dump();
    
  }
  else {
    
  if(selector3142a::allianceBlue) {
    // blue auton
    blue_auton();
  }

  else {
    //red auton
    red_auton();
  }

  }

  }
  // we have selected skills
  else {
    //run skills here
    run_auton_skills();
  }*/
  


}

task blue_intakes;
task blue_indexer;
task blue_flywheel;
void blue_auton() {
  moveInch(-10,50);
    task deployTask = task( unlock_robot_task );
  do {
    task::sleep(5);
  }while(!unlocked);
  deployTask.stop();

    blue_intakes = task( intakeTask );
  blue_indexer = task( indexerTask );
  blue_flywheel = task( flywheelTask );  
  turnToDegree(50.0_deg);

    RUN_INTAKES = true;
  RUN_INDEXERS = true;
  RUN_FLYWHEEL = true;
  
  moveInch(9, 50,1000);

  SCORE = true;
  task::sleep(600);
  moveInch(- 9, 50,1000);
}

void blue_auton2() {
  
  // align with goal #1
  strafeInch(7,50);


  // deploying robot
  task deployTask = task( unlock_robot_task );
  do {
    task::sleep(5);
  }while(!unlocked);
  deployTask.stop();

  // start subsystem tasks
  // task matchIntakes = task( intakeTask );
  // task matchIndexer = task( indexerTask );
  // task matchFlywheel = task( flywheelTask );
  blue_intakes = task( intakeTask );
  blue_indexer = task( indexerTask );
  blue_flywheel = task( flywheelTask );  

  //score in goal 1
  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;
  
  moveInch(7, 50);
  STOP_INDEXERS_BOTTOM_DETECTED = true;
  moveInch(9, 50,1000);
  task::sleep(200);
  SCORE = true;
  task::sleep(500);

  //moving to goal 2
  STOP_INTAKES = false;
  STOP_INDEXERS_BOTTOM_DETECTED = false;
  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;

  moveInch(-13,50);
  
  task::sleep(100);

  RUN_INTAKES = false;
  // INTAKE_OUT = false;
  STOP_INTAKES = true;

  turnToDegree(-50.0_deg);

  strafeInch(-23, 50);
  RUN_INDEXERS = false;
  STOP_INDEXERS = true;
  
  task::sleep(100);

  // //scoring in goal 2
  // STOP_INDEXERS = true;
  moveInch(7.5, 40,750);
  SCORE = true;
  task::sleep(600);
  RUN_INTAKES = true;
  INTAKE_OUT = true;
  moveInch(-15.5, 40);
  STOP_FLYWHEEL_TOP_DETECTED = false;
  STOP_FLYWHEEL = true;
  INTAKE_OUT = false;
  RUN_INTAKES = false;
  STOP_INTAKES = true;
  task::sleep(100);
  strafeInch(-42, 50);
  task::sleep(100);
  turnToDegree(-103.0_deg);
  RUN_FLYWHEEL = true;
  STOP_INTAKES = false;
  
  RUN_INTAKES = true;
  STOP_INDEXERS = false;
  RUN_INDEXERS = true;
  moveInch(12,80,1000);
  task::sleep(1000);
  moveInch(-18,50);
  blue_intakes.stop();
  blue_indexer.stop();
  blue_flywheel.stop();
}
task red_intakes;
task red_indexer;
task red_flywheel;

void red_auton() {

  // align with goal #1
  strafeInch(7,50);


  // deploying robot
  task deployTask = task( unlock_robot_task );
  do {
    task::sleep(5);
  }while(!unlocked);
  deployTask.stop();

  // start subsystem tasks
  // task matchIntakes = task( intakeTask );
  // task matchIndexer = task( indexerTask );
  // task matchFlywheel = task( flywheelTask );

  red_intakes = task( intakeTask );
  red_indexer = task( indexerTask );
  red_flywheel = task( flywheelTask );  
  //score in goal 1
  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;
  
  moveInch(11.5, 50,1250);
  STOP_INDEXERS_BOTTOM_DETECTED = true;
  moveInch(3,50,300);
  task::sleep(200);
  SCORE = true;
  task::sleep(500);

  //moving to goal 2
  STOP_INTAKES = false;
  STOP_INDEXERS_BOTTOM_DETECTED = false;
  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;

  moveInch(-15,50);
  
  task::sleep(100);

  RUN_INTAKES = false;
  // INTAKE_OUT = false;
  STOP_INTAKES = true;

  turnToDegree(-50.0_deg);

  strafeInch(-20, 50);
  RUN_INDEXERS = false;
  STOP_INDEXERS = true;
  
  task::sleep(100);

  // //scoring in goal 2
  // STOP_INDEXERS = true;
  moveInch(8, 40,1250);
  SCORE = true;
  task::sleep(600);
  moveInch(-14, 40);
  STOP_FLYWHEEL_TOP_DETECTED = false;
  STOP_FLYWHEEL = true;
  task::sleep(100);
  strafeInch(-38, 50);
  task::sleep(100);
  turnToDegree(-110.0_deg);
  RUN_FLYWHEEL = true;
  STOP_INTAKES = false;
  RUN_INTAKES = true;
  STOP_INDEXERS = false;
  //RUN_INDEXERS = true;
  Indexer.spin(forward,300,rpm);
  moveInch(16,80,1250);
  task::sleep(1250);
  moveInch(-18,50);
    STOP_INTAKES = true;
  RUN_INTAKES = false;
  Indexer.spin(forward,0,rpm);
  STOP_INDEXERS = true;
  RUN_FLYWHEEL = false;
  STOP_FLYWHEEL = true;
  // matchFlywheel.stop();
  // matchIndexer.stop();
  // matchIntakes.stop();

    red_intakes.stop();
  red_indexer.stop();
  red_flywheel.stop();

}

void middle_goal_dump() {

  int timer = 0;

  while(timer < 6000) {
  Flywheel.spin(fwd,600,rpm);
  Indexer.spin(fwd,10,volt);
  timer += 10;
  task::sleep(10);
  }
  Flywheel.stop();
  Indexer.stop();

}

int unlock_robot_task() {
  LOG("UNLOCKING ROBOT");
  
  int timer = 0;

  while(!unlocked) {

  Flywheel.spin(forward,100,rpm);
  IntakeL.spin(reverse,600,rpm);
  IntakeR.spin(reverse,600,rpm);

  timer += 10;

  if(timer > unlockTime) {
    unlocked = true;
  }

  task::sleep(10);

  }

  LOG("ROBOT UNLOCKED!!");
  IntakeL.stop();
  IntakeR.stop();
  Flywheel.stop();
  return 1;
}