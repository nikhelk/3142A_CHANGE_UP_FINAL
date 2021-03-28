using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rightFront;
extern motor leftFront;
extern motor leftBack;
extern motor rightBack;
extern triport Expander19;
extern encoder leftEncoder;
extern motor IntakeL;
extern motor IntakeR;
extern motor Indexer;
extern motor Flywheel;
extern encoder backEncoder;
extern encoder rightEncoder;
extern controller Controller1;
extern inertial inert;
extern line topLine;
extern line middleLine;
extern line bottomLine;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );