#include "odometry.h"

#include <cmath>

// defining global instance of our position array that we use throughout the code
sPos gPos;
/*
Copyright (c) 2018 5225A E-bot PiLons
Modifications nikhelkrishna
2020-31-7: Modify constants for bot use

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void initOdom(sPos& position) {

  position.leftLst = leftEncoder.position(degrees);
  position.rightLst = rightEncoder.position(degrees);
  position.backLst = backEncoder.position(degrees);

}
void updateOdom(sPos& position) {

    int left = leftEncoder.position(degrees);
    int right = rightEncoder.position(degrees); 
    int back = backEncoder.position(degrees);
    double deltaL = (left - position.leftLst) * SPIN_TO_IN_LR ; // The amount the left side of the robot moved
    double deltaR = -1* (right - position.rightLst) * SPIN_TO_IN_LR; // The amount the right side of the robot moved (reversed)
    double deltaB = (back - position.backLst) * SPIN_TO_IN_B;                // The amount the back side of the robot moved

    // Update the last values
    position.leftLst = left;
    position.rightLst = right;
    position.backLst = back;

    double h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
    double i; // Half on the angle that I've traveled
    double h2; // The same as h but using the back instead of the side wheels

    double deltaA = (deltaL - deltaR) / (L_DISTANCE_IN + R_DISTANCE_IN); // The angle that I've traveled
    if (deltaA)
    {
      double r = deltaR / deltaA; // The radius of the circle the robot travels around with the right side of the robot
      i = deltaA / 2.0;
      h = ((r + L_DISTANCE_IN) * sin(i)) * 2.0;

      double r2 = deltaB / deltaA; // The radius of the circle the robot travels around with the back of the robot
      h2 = ((r2 + B_DISTANCE_IN) * sin(i)) * 2.0;
    }
    else
    {
      // if we have not changed our angle then the hypotenuse is simply the change of the side
      h = deltaR;
      i = 0;

      h2 = deltaB;
    }
    double p = i + inert.rotation()*M_PI/180; // The global ending angle of the robot (we use the inertial sensor value converted to radians for the last angle)

    // conversion from polar to cartesian
    position.y += h * cos(p);
    position.x += h * sin(p);

    position.x += h2 * cos(p);
    position.y += h2 * -sin(p);

    position.a = inert.rotation()*M_PI/180;
   //  position.a += deltaA;

    std::cout << "ODOM: " <<  position.x << " " << position.y << " " <<position.a*180/M_PI<<std::endl;




}

/// WE WOULD LIKE TO THANK 5225A FOR SHARING AND EXPLAINING THEIR ODOM SYSTEM AND CODE
int trackPosition(void)
{
  initOdom(gPos);

  while (true)
  {
    updateOdom(gPos);
    task::sleep(15);
  }
  return 1;
}


void setOdomOrigin(double x, double y, double a,sPos& position)
{
  position.x = x;
  position.y = y;
  position.a = a;

  inert.setRotation(a*(180/M_PI),degrees);
}
