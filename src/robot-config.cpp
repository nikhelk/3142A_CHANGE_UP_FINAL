#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
triport Expander19 = triport(PORT19);
motor rightFront = motor(PORT1, ratio18_1, true);
motor leftFront = motor(PORT2, ratio18_1, false);
motor leftBack = motor(PORT4, ratio18_1, false);
motor rightBack = motor(PORT3, ratio18_1, true);
encoder leftEncoder = encoder(Expander19.E);
motor IntakeL = motor(PORT7, ratio6_1, false);
motor IntakeR = motor(PORT6, ratio6_1, true);
motor Indexer = motor(PORT11, ratio6_1, false);
motor Flywheel = motor(PORT10, ratio6_1, true);
encoder backEncoder = encoder(Expander19.G);
encoder rightEncoder = encoder(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);
inertial inert = inertial(PORT9);
line topLine = line(Expander19.D);
line middleLine = line(Expander19.C);
line bottomLine = line(Expander19.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}