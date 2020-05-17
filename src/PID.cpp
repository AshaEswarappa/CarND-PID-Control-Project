#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */

    Kp = Kp_;  //Proportional gain

    Ki = Ki_; //Integral gain 
    
    Kd = Kd_; //Differential gain

    prev_cte = 0; // Initialize the previous cross track error used for first error calculation of differntial 

    counter = 0; //Initialize the counter
}

void PID::UpdateError(double cte) 
{
  /**
   * TODO: Update PID errors based on cte.
   */
    /*Assignment of cross track errot to individual parameters of PID controller */
   p_error =  cte; /*proportional error */

   d_error = (cte - prev_cte); /*Differential error */

   i_error += cte; /*Integral error */

  /*stored the error for next calculation of differential error */

  prev_cte = cte;

  counter += 1; //update counter after error update

}

double PID::TotalError() 
{
  /**
   * TODO: Calculate and return the total error
   */
   Total_Err = ((-Kp * p_error) +(-Ki *i_error) + (-Kd * d_error));

  return Total_Err;  // TODO: Add your total error calc here!
}