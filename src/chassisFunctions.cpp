#include "chassisFunctions.h"
#include "PID.h"
#include <cmath>



void moveToPointAndAngle(double target_x, double target_y, double target_theta) {

  int timeOut = 125; //if we are there for 125 msec we are ther
  double accelTime = 750;
  double currentTime = 0;
  double coefTime;
  double errorThreshold = 1.25; //if we are <= 1.25 inches we are there
  double prevDistanceError =0;
  int close_enough_timer = 0;

  int not_moved_timer = 0;

  bool atTarget = false;

  posPID distancePID(12, 27.5,75,-75); //PD for the main driving power to a point use 60,-60 as bounds cause we are using pct

  posPID anglePID(15.5,12,40,-40); //angle PD for getting to desired angle

  while( !atTarget ){
    double angleError = (target_theta - gPos.a);
    double distanceError = sqrt(pow((target_x - gPos.x), 2) + pow((target_y -gPos.y), 2)); //using distance formula to find error to point

    double anglePower = anglePID.calculatePower(angleError); //Final value to pass to the motor, taking P and D loops into account.
    double distancePower = distancePID.calculatePower(distanceError); //Final drive value to pass to the motor, taking P and D loops into account.

    if(currentTime < accelTime) {
      coefTime = (currentTime) / (accelTime);
      LOG(currentTime);
    }
    // use the atan2 function to find the heading towards the desired point
    double direction = atan2(target_y - gPos.y, target_x - gPos.x);
    setDriveVelocity(
      (distancePower*(cos(gPos.a + direction - M_PI/4)) + anglePower)*coefTime,// The robot uses trigonometry to determine the ideal value to pass to a motor
      (distancePower*(cos(3*M_PI/4-direction-gPos.a))-anglePower)*coefTime, // given each wheel's 45 degree offset. This value for the drive is then added
      (distancePower*(cos(3*M_PI/4- direction -gPos.a))+anglePower)*coefTime, //RB to the value for turning, which is negative on the right side of the bot.
      (distancePower*(cos(gPos.a + direction - M_PI/4)) - anglePower)*coefTime 
    );


    if(std::abs(distanceError) <errorThreshold ) {
      close_enough_timer += 10;

    }
    if(std::abs(distanceError-prevDistanceError)<0.5) {
      not_moved_timer += 2;
    }
    else {
      close_enough_timer = 0;
      not_moved_timer = 0;
    }
    if(close_enough_timer> timeOut ) {
      atTarget = true;
    }
    prevDistanceError = distanceError;
    currentTime+= 10;
    LOG(coefTime);
    task::sleep(10); 
  }
  LOG("DONE MOVING TO POINT");
  holdDrive();
}

void turnToDegree(double degree) {

  // initialize an anglePID 
posPID anglePID(28.5,32.5,12,-12);

  int close_enough_timer = 0; //timer for how long we have been close to the target

  int timeOut = 250; //250 ms of being close and we can exit the PID loop

  bool atTarget = false;

  double errorThreshold = 1.5_deg; // if we have an error if <1.5 degrees then we are close enough

  while (!atTarget)
  {
    // correction of angle haeding using voltage output (set up a PID for both
    // left and right sides of the x drive using motor encoder values for
    // current and destination)
    long double anglePower = anglePID.calculatePower(degree, inert.rotation(degrees)*M_PI/180);
    LOG(std::abs(degree-inert.rotation(degrees)*M_PI/180));


    setDriveVoltage(anglePower, -anglePower, anglePower, -anglePower);

    // increment timeout if we are below threshold
    if(std::abs(degree-inert.rotation(degrees)*M_PI/180)< errorThreshold){
      close_enough_timer += 10;
    }
    else {
      close_enough_timer = 0;
    }
    
    // close enough for long enough, we are there
    if(close_enough_timer > timeOut) {
      atTarget = true;
    }
    task::sleep(10);
  }
  LOG("DONE TURNING TO ANGLE");
  holdDrive();

}
void strafeInch(double distance, double speed) {
  
  //reset the encoder
  backEncoder.setPosition(0,degrees);

  // convert our inches input to encoder ticks
  double ticks = 360*(distance)/(2.75*M_PI);

  // moving right code
  if(distance > 0) {
    while(backEncoder.position(degrees) < ticks){
      // move the robot to the right while we havent reached the desired encoder distance
      setDriveVelocity(speed,-speed,-speed,speed);
    }
  }
  //moving left code
  else {
    
    while(backEncoder.position(degrees) > ticks){
      // move the robot to the left while we havent reached the desired encoder distance
      setDriveVelocity(-speed,speed,speed,-speed);
    }
  }
  //stop the robot
  brakeDrive();
}
void moveInch(double distance, double speed, double time){

int initLeft = leftEncoder.position(degrees);
  int initRight = rightEncoder.position(degrees);
  double timer = 0;
  double ticks = 360*(distance)/(2.75*M_PI); //converting input to encoder ticks

  // move up code
  if(distance > 0) {
    // for the elapsed distance we use an average between the left and right encoders
    while((leftEncoder.position(degrees))-initLeft-(rightEncoder.position(degrees)-initRight)/2< ticks) {
      setDriveVelocity(speed,speed,speed,speed);
      timer += 2;
      if(timer > time) {
        break;
      }
      task::sleep(2);
    }
  }
  // move backwards code
  else {
    // for the elapsed distance we use an average between the left and right encoders
    while((leftEncoder.position(degrees)-rightEncoder.position(degrees))/2 > ticks) {
      setDriveVelocity(-speed,-speed,-speed,-speed);
      timer += 2;
      if(timer > time) {
        break;
      }
      task::sleep(2);
      
    }
  }
  //stop bot
  brakeDrive();
}
void moveInch(double distance, double speed) {

  //reset the left and right encoders
  int initLeft = leftEncoder.position(degrees);
  int initRight = rightEncoder.position(degrees);

  double ticks = 360*(distance)/(2.75*M_PI); //converting input to encoder ticks

  // move up code
  if(distance > 0) {
    // for the elapsed distance we use an average between the left and right encoders
    while((leftEncoder.position(degrees))-initLeft-(rightEncoder.position(degrees)-initRight)/2< ticks) {
      setDriveVelocity(speed,speed,speed,speed);
    }
  }
  // move backwards code
  else {
    // for the elapsed distance we use an average between the left and right encoders
    while((leftEncoder.position(degrees)-rightEncoder.position(degrees))/2 > ticks) {
      setDriveVelocity(-speed,-speed,-speed,-speed);
    }
  }
  //stop bot
  brakeDrive();
}




/// Print inertial sensor value to controller screen to make sure it's not drifting too much
int print_inertial_drift_task() {
  while(true) {

  Controller1.Screen.print("%f", inert.rotation());
  Controller1.Screen.clearLine();
  task::sleep(200);
  }
}

void setDriveVoltage(double leftFrontVoltage, double rightFrontVoltage , double leftBackVoltage, double rightBackVoltage) {
  leftFront.spin(fwd,leftFrontVoltage,volt);
  rightFront.spin(fwd,rightFrontVoltage,volt);
  leftBack.spin(fwd,leftBackVoltage,volt);
  rightBack.spin(fwd,rightBackVoltage,volt);
}

void setDriveVelocity( double leftFrontVelocity, double rightFrontVelocity, double leftBackVelocity, double rightBackVelocity ) {
  leftFront.spin(directionType::fwd, leftFrontVelocity, velocityUnits::pct);
  leftBack.spin(directionType::fwd, leftBackVelocity, velocityUnits::pct);
  rightBack.spin(directionType::fwd, rightBackVelocity, velocityUnits::pct);
  rightFront.spin(directionType::fwd, rightFrontVelocity, velocityUnits::pct);
}

void holdDrive() {
  leftFront.stop(brakeType::hold);
  leftBack.stop(brakeType::hold);
  rightBack.stop(brakeType::hold);
  rightFront.stop(brakeType::hold);
}

void brakeDrive() {
  leftFront.stop(brakeType::brake);
  leftBack.stop(brakeType::brake);
  rightBack.stop(brakeType::brake);
  rightFront.stop(brakeType::brake);
}