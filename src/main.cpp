/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nikhel krishna                                            */
/*    Created:      Wed Mar 10 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightFront           motor         1               
// leftFront            motor         2               
// leftBack             motor         4               
// rightBack            motor         3               
// Expander19           triport       19              
// leftEncoder          encoder       E, F            
// IntakeL              motor         7               
// IntakeR              motor         6               
// Indexer              motor         11              
// Flywheel             motor         10              
// backEncoder          encoder       G, H            
// rightEncoder         encoder       A, B            
// Controller1          controller                    
// inert                inertial      9               
// topLine              line          D               
// middleLine           line          C               
// bottomLine           line          B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Selector/selectorAPI.h"
#include "Selector/selectorImpl.h"
using namespace vex;

competition Competition;

/// set up robot
void pre_auton() {

  // callbacks for brain press and release 
  Brain.Screen.pressed( selector3142a::userTouchCallbackPressed ); // set up callback for brain screen press
 
  Brain.Screen.released( selector3142a::userTouchCallbackReleased ); // set up callback for brain screen release
  
  // calibrate inertial and printing status to the controller screen
  inert.calibrate();
  do {

    Controller1.Screen.print("Calibrating Inert");
    task::sleep(200);

    Controller1.Screen.clearLine(3);
  } while((inert.isCalibrating()) );
  // task inertPrint( print_inertial_drift_task );

  // resetting the encoders and motors
  leftEncoder.resetRotation();
  rightEncoder.resetRotation();
  backEncoder.resetRotation();
  leftFront.resetPosition();
  leftBack.resetPosition();
  rightBack.resetPosition();
  rightFront.resetPosition();

  // setting the odom values to x = 0 y = 0 theta = 0 
  setOdomOrigin(0,-2,0,gPos);
}

void test() {
  task poseTrack = task( trackPosition );
  task::sleep(200);
  moveToPointAndAngle(14.6,-1.69,0.0_deg);


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

  RUN_INTAKES = true;
  RUN_INDEXERS = true;
  
  STOP_FLYWHEEL_TOP_DETECTED = true;

  //getting first ball
  moveToPointAndAngle(12.8,10,-0.74_deg);
  RUN_INDEXERS = false;
  STOP_INDEXERS_BOTTOM_DETECTED = true;
  RUN_INDEXERS = false;
  task::sleep(100);
  moveToPointAndAngle(12.6,23.9,.92_deg);
  task::sleep(100);

  //aligning to goal #1
  turnToDegree(-45.0_deg);

  RUN_INTAKES = false;
  STOP_INTAKES = true;
  //moving to goal #1 and scoring
  moveToPointAndAngle(2,30,-44.0_deg);

  SCORE = true;
  task::sleep(500);

  //backing up 

  moveToPointAndAngle(12.8,24.5,-42.0_deg);
  STOP_FLYWHEEL_TOP_DETECTED = true;
  
  task::sleep(100);

  //going to goal 2 and scoring
  turnToDegree(90.0_deg);
  RUN_INDEXERS = true;
  STOP_INDEXERS_BOTTOM_DETECTED = false;
  // RUN_INDEXERS = false;
  // STOP_INDEXERS = false;
  // STOP_INDEXERS_BOTTOM_DETECTED = true;
    RUN_INTAKES = true;
    STOP_INTAKES = false;
  moveToPointAndAngle(26.6,27,90.0_deg);
  RUN_INDEXERS = false;
  STOP_INDEXERS_BOTTOM_DETECTED = true;
  moveToPointAndAngle(41.2,29,90.0_deg);
  task::sleep(100);
  turnToDegree(0.0_deg);
  moveToPointAndAngle(41.2,35,0.0_deg);
  RUN_INTAKES = false;
  STOP_INTAKES = true;
  SCORE = true;
  task::sleep(600);
  
  //back out
  STOP_INDEXERS_BOTTOM_DETECTED = false;
  STOP_INTAKES = false;
  RUN_INTAKES = true;
  INTAKE_OUT = true; //intake out so we don't pick up blue ball
  moveToPointAndAngle(41.2,29,0.0_deg);
  task::sleep(100);
  // // // //moving to goal 3 and scoring
  turnToDegree(81.0_deg);
  STOP_INDEXERS_BOTTOM_DETECTED = false;
  RUN_INDEXERS = true;
  STOP_FLYWHEEL_TOP_DETECTED = true;
  moveToPointAndAngle(87.2,43.4,74.0_deg);
  RUN_INTAKES = false;
  INTAKE_OUT = false;
  STOP_INTAKES = true;
  task::sleep(100);
  turnToDegree(45.0_deg);
  moveToPointAndAngle(91.1,47.9,42.0_deg);
  SCORE = true;
  task::sleep(500);

  // //moving to goal 4 and scoring
  // moveToPointAndAngle(-2.6,-10.8,1.67_deg);
  // task::sleep(100);
  // turnToDegree(112.0_deg);
  // RUN_INTAKES = true;
  // STOP_INTAKES = false;
  // STOP_FLYWHEEL_TOP_DETECTED = true;
  // moveToPointAndAngle(-3.22,-11.9,112.0_deg);
  // task::sleep(100);
  // moveToPointAndAngle(9.4,-13.5,108.0_deg);
  // task::sleep(100);
  // turnToDegree(128.0_deg);

  // moveToPointAndAngle(35.9,-28.7,128.0_deg);
  // task::sleep(100);
  // RUN_INTAKES = false;
  // STOP_INTAKES = true;
  // RUN_INDEXERS = true;
  // STOP_INDEXERS = false;
  // turnToDegree(40.0_deg);
  // moveToPointAndAngle(38.8,-25.4, 40.0_deg);
  // SCORE = true;
  // task::sleep(500);

  // //moving to goal 5 and scoring
  // moveToPointAndAngle(111.5,-20.5,90.0_deg);
  // task::sleep(100);
  // setOdomOrigin(111,-20.5,90.0_deg,gPos);
  // turnToDegree(180.0_deg);
  // RUN_INTAKES = true;
  // STOP_INTAKES = false;
  // STOP_FLYWHEEL_TOP_DETECTED = true;
  // RUN_INDEXERS = true;
  // STOP_INDEXERS = false;
  // moveToPointAndAngle(111,-62.5,183.0_deg);
  // task::sleep(100);
  // turnToDegree(120.0_deg);
  //   RUN_INTAKES = false;
  // STOP_INTAKES = true;
  //   RUN_INDEXERS = false;
  // STOP_INDEXERS = true;
  // moveToPointAndAngle(122.5,-70.75,130.0_deg);
  // SCORE = true;
  // task::sleep(500);

  // // move to goal 6
  //  moveToPointAndAngle(117.5,-65.75,130.0_deg);
  //  task::sleep(100);
  //  turnToDegree(270.0_deg);
  // RUN_INTAKES = true;
  // STOP_INTAKES = false;
  // STOP_FLYWHEEL_TOP_DETECTED = true;
  // RUN_INDEXERS = true;
  // STOP_INDEXERS = false;
  // moveToPointAndAngle(50,-65.75,270.0_deg);
  // task::sleep(100);
  // turnToDegree(180.0_deg);
  // moveToPointAndAngle(50,-68,180.0_deg);
  // RUN_INTAKES = false;
  // STOP_INTAKES = true;
  // RUN_INDEXERS = false;
  // STOP_INDEXERS = true;
  // SCORE = true;
  // task::sleep(500);

  // // move from goal 6 to center goal


  // moveToPointAndAngle(50,-65.75,180.0_deg);
  // task::sleep(100);
  // turnToDegree(0.0_deg);
  // RUN_INTAKES = true;
  // STOP_INTAKES = false;
  // STOP_FLYWHEEL_TOP_DETECTED = true;
  // RUN_INDEXERS = true;
  // STOP_INDEXERS = false;
  // //pick up ball
  // moveToPointAndAngle(50,-50.75,0.0_deg);
  // task::sleep(100);
  // //strafe a little bit to align the puncher
  // moveToPointAndAngle(55,-50.75,0.0_deg);
  // task::sleep(100);
  // //punch out ball
  // moveToPointAndAngle(55,-40,0.0_deg);
  // task::sleep(200);
  // moveToPointAndAngle(55,-45,0.0_deg);
  // task::sleep(100);
  // SCORE = true;
  // task::sleep(500);
  // moveToPointAndAngle(55,-55,0.0_deg);
  // RUN_INTAKES = false;
  // STOP_INTAKES = true;
  // RUN_INDEXERS = false;
  // STOP_INDEXERS = true;

  // // move from goal 6 to goal 7

  // // move from goal 7 to center goal

  
  



  matchFlywheel.stop();
  matchIndexer.stop();
  matchIntakes.stop();
  poseTrack.stop();
}

void test2() {
  task poseTrack( trackPosition );
  task::sleep(200);
  setOdomOrigin(0,0,0.0_deg,gPos);
  while(true){task::sleep(100);}
}
int main() {
  LOG("ENTERING MAIN");

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
   pre_auton();

  task::sleep(200);

  // // Competition callbacks
  //Controller1.ButtonA.pressed(usercontrol);
  Competition.drivercontrol( usercontrol );
  Competition.autonomous( autonomous );
 // Controller1.ButtonA.pressed( autonomous );

  while(true){
    // LOG(inert.rotation(degrees));
    task::sleep(100);}

}
