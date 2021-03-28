#include "subsystems.h"

// defining all the booleans false at compile-time
// when one of these variable is set to "true" during the autonomous run
// the robot inherts the specifics of that motion
bool RUN_INTAKES = false;
bool STOP_INTAKES = false;
bool STOP_FLYWHEEL = false;
bool STOP_FLYWHEEL_TOP_DETECTED = false;
bool SCORE = false;
bool SCORE2 = false;
bool RUN_FLYWHEEL = false;
bool RUN_INDEXERS = false;
bool STOP_INDEXERS = false;
bool STOP_INDEXERS_BOTTOM_DETECTED = false;
bool INTAKE_OUT = false;

// line sensor value thresholds for the indexing
int TOP_LINE_THRESHOLD = 70;
int BOTTOM_LINE_THRESHOLD = 69;

int intakeTask() {
 while(true){
   // when the "run intakes" setting is activated
   if(RUN_INTAKES) {
    // we want to slow down our intakes a little if we are indexing to the bottom line sensor
    if(STOP_INDEXERS_BOTTOM_DETECTED) {
      IntakeL.spin(fwd,400,rpm);
      IntakeR.spin(fwd,400,rpm);

    }
    //reverse intakes
    else if(INTAKE_OUT) {

      IntakeL.spin(reverse,500,rpm);
      IntakeR.spin(reverse,500,rpm);

    }
    // full speed ahead!
    else {
    IntakeL.spin(fwd,600,rpm);
    IntakeR.spin(fwd,600,rpm);
    }


   }
   // stop intakes when setting is activated
   if(STOP_INTAKES) {

    IntakeL.spin(fwd,0,rpm);
    IntakeR.spin(fwd,0,rpm);

   }

    task::sleep(10);

  }
  return 1;
}
int indexerTask() {

  while(true) {
    
    // spin indexers when setting is on
    if(RUN_INDEXERS) {
      Indexer.spin(fwd,500,rpm);
    }
    // stop the indexers
    if(STOP_INDEXERS) {
      Indexer.spin(fwd,0,rpm);
    }

    // when indexing setting is on we are going to simply index a ball to the bottom sensor and stop the indexer
    if(STOP_INDEXERS_BOTTOM_DETECTED) {

      // while we are over the threshold run the indexers
      if(bottomLine.value(pct) > BOTTOM_LINE_THRESHOLD) {
        Indexer.spin(fwd,150,rpm);
      }
      // stop the indexers once we have gone below (i.e. ball is detecded by the sensor)
      else {
        Indexer.setBrake(hold);
        Indexer.spin(fwd,0,rpm);

      }

    }
    task::sleep(10);

  }
  return 1;
}

int flywheelTask() {
  while(true) {
    
    // stop flywheel when setting is on
    if(STOP_FLYWHEEL) {
      Flywheel.spin(fwd,0,rpm);
    }

    // run flywheel at full speed
    if(RUN_FLYWHEEL) {
      Flywheel.spin(fwd,600,rpm);
    }

    // scoring macro
    if(SCORE) {

      // automatically turn off other settings
      STOP_FLYWHEEL_TOP_DETECTED = false;
      STOP_FLYWHEEL = false;

      //spin flywheels for 1/2 a second and then we are done
      Flywheel.spin(fwd,600,rpm);
      task::sleep(600);
      SCORE = false;
      Flywheel.spin(fwd,0,rpm);
    }

    if(SCORE2) {

      // automatically turn off other settings
      STOP_FLYWHEEL_TOP_DETECTED = false;
      STOP_FLYWHEEL = false;

      //spin flywheels for 1/2 a second and then we are done
      Flywheel.spin(fwd,600,rpm);
      task::sleep(1250);
      SCORE2 = false;
      Flywheel.spin(fwd,0,rpm);
    }

    // if we want to index to the top line sensor we use this (very similar to indexer indexeing code)
    if(STOP_FLYWHEEL_TOP_DETECTED) {
      if(topLine.value(pct) > TOP_LINE_THRESHOLD) {
        Flywheel.spin(fwd,25,rpm);
      }
      else {
        Flywheel.setBrake(hold);
        Flywheel.spin(fwd,0,rpm);
      }

  }
  task::sleep(10);
  
}
return 1;
}

