#include "usercontrol.h"
#include <cmath>



/// Used to ramp the turning speed, for finer control at lower speeds. Input is the joystick value
double cubic(double input) { 

 

  if (input != 0) {return (pow(input,3))/(100*std::abs(input));}
  else {return 0;}
}

void usercontrol() {
  blue_intakes.stop();
  blue_indexer.stop();
  blue_flywheel.stop();

  red_intakes.stop();
  red_indexer.stop();
  red_flywheel.stop();

  int TOP_LINE_THRESHOLD_USER = 70;
  int MIDDLE_LINE_THRESHOLD_USER = 67;
  int BOTTOM_LINE_THRESHOLD_USER = 70;
  LOG("ENTERING USERCONTROL");
  task deployTask = task( unlock_robot_task );
  do {
    task::sleep(5);
  }while(!unlocked);
  deployTask.stop();
  while(true) {

  //DRIVING
    double throttle = Controller1.Axis3.value();
    double strafe = Controller1.Axis4.value();
    double turn = cubic(Controller1.Axis1.value());

    // here we have a custom deadzone so the robot wont move if the value is less than 5
    if(std::abs((throttle+strafe+turn)) <5) {
      leftFront.stop(brakeType::brake);
      // eftFront.spin(directionType::fwd, 0, velocityUnits::pct);
    }
    else {
      leftFront.spin(directionType::fwd, (throttle+strafe+turn), velocityUnits::pct);
    }

    if(std::abs((throttle-strafe+turn)) <5) {
      leftBack.stop(brakeType::brake);
      // leftBack.spin(directionType::fwd, 0, velocityUnits::pct);
    }
    else {
      leftBack.spin(directionType::fwd, (throttle-strafe+turn), velocityUnits::pct);
    }

    if(std::abs((throttle+strafe-turn)) <5) {
      rightBack.stop(brakeType::brake);
     //  rightBack.spin(directionType::fwd, 0, velocityUnits::pct);
    }
    else {
      rightBack.spin(directionType::fwd, (throttle+strafe-turn), velocityUnits::pct);
    }

    if(std::abs((throttle-strafe-turn)) <5) {
      rightFront.stop(brakeType::brake);
    //  rightFront.spin(directionType::fwd, 0, velocityUnits::pct);
    }
    else {
      rightFront.spin(directionType::fwd, (throttle-strafe-turn), velocityUnits::pct);
    }

    // intake
    if(Controller1.ButtonL1.pressing()&& !Controller1.ButtonL2.pressing())
    {
      IntakeL.spin(fwd,600,rpm);
      IntakeR.spin(fwd,600,rpm);
    }

    // outtake
    else if (Controller1.ButtonL2.pressing()&& !Controller1.ButtonL1.pressing())
    {
      IntakeL.spin(fwd,-600,rpm);
      IntakeR.spin(fwd,-600,rpm);
    }

    // stop intakes
    else
    {
      IntakeL.spin(fwd,0,rpm);
      IntakeR.spin(fwd,0,rpm);
    }


    // indexing controls
    if (Controller1.ButtonR2.pressing())
    {
      Indexer.spin(fwd,500,rpm);
      // while the ball isnt at the shooting position run the indexer
      // if(topLine.value(pct) > TOP_LINE_THRESHOLD_USER ) {
      // Indexer.spin(fwd,500,rpm);
      // Flywheel.spin(fwd,25,rpm);
      // }
      // else{
      //   // when we have reached the the top then stop stop the flywheel
      //   Flywheel.spin(fwd,0,rpm);
      //   Flywheel.setBrake(hold);

      //   //index the next ball
      //   if(middleLine.value(pct) > MIDDLE_LINE_THRESHOLD_USER) {
      //     Indexer.spin(fwd,500,rpm);
      //   }
      // }
    }

    // index balls down
    else if(Controller1.ButtonB.pressing()) {
      Indexer.spin(fwd,-300,rpm);
    }

    else
    {
      Indexer.spin(fwd,0,rpm);

    }

    // shooting controls (R2 fires balls)
    if (Controller1.ButtonR1.pressing())
    {
      // shoots  ball
      Flywheel.spin(fwd,500,rpm);
    }
    // descoring mech
    else if ((Controller1.ButtonB.pressing()))
    {
      Flywheel.spin(fwd,-300,rpm);
    }

    else
    {
      Flywheel.spin(fwd,0,rpm);
    }



  LOG(topLine.value(pct),middleLine.value(pct),bottomLine.value(pct),"usercontrol");

  task::sleep(20);
  
  }
}