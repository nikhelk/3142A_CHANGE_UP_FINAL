#pragma once

#include "vex.h"

/**
 * class posPID 
 * used to create posPID objects 
 * PID is a feedback loop which allows us to use sensor values (encoder) to output a desired power based on error
 */

class posPID
{
private:
  double m_kP;
  double m_kD;

  double m_error;
  double m_prevError;
  double m_proportional;
  double m_derivative;

  int m_upperBound; //max voltage
  int m_lowerBound; //min voltage
  double m_power;

public:

  /**
   * default posPID constructor for values inputted in the FourMotorDrive constructor
   */
  posPID();

  /**
   * sets the PD values for custom PIDs in FourMotorDrive constructor
   * @param kP desired kP value
   * @param kD desired kD value
   */
  void setPD(double kP, double kD);
  
  
  /**
   * Creates a PD controller for drivetrain
   * @param kP value
   * @param kD value
   */

  posPID(double kP, double kD, int upperBound, int lowerBound);



  /**
   * Calculates power of PD drive controller given target and current
   * @param targetPos  desired position of robot
   * @param currentPos current position of robot
   * @return output power of controller
   */

  double calculatePower(double targetPos, double currentPos);


  /**
   * Calculates power of PD drive controller given error variable
   * @param error error variable to calculate off of
   * @return output power of controller
   */

  double calculatePower(double error);
 
  /**
   * gets the error of the PD controller
   * @return error of controller
   */

  double getError() const { return (m_error); }

  /// gets kP value of controller
  double getKp() const {return (m_kP);}

  /// gets kD value of controller 
  double getKd() const {return(m_kD);}

  /**
   * gets the power of the PD controller
   * @return error of controller
   */
  double getPower() const { return (m_power); }
};


/**
 * struct pidTimer
 * timers for pid timeout
 */

struct pidTimer 
{
  int close; //if robot is close to target
  int notMoved; //if robot has not moved
};
