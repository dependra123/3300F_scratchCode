#include "main.h"

double PID::compute(double current) {
    error = target - current;
    derivative = error - lastError;
    

    if (pidConstants.kI != 0) {
        if (fabs(error) < pidConstants.start_i)
        integral += error;

        if(util::sign(error) != util::sign(lastError))
        integral = 0;
    }

    output = (error * pidConstants.kP) + (integral * pidConstants.kI) + (derivative * pidConstants.kD);

    lastError = error;

    return output;
}



/**
 * @brief  Set PID constants
 * @param  pid_constants PID constants
 * @return void
*/
void PID::setConstants(constants pid_constants){
    pidConstants = pid_constants;
}

/**
 * @brief  Get PID constants
 * @return PID constants
*/
PID::constants PID::getConstants(){
     return pidConstants;
}


//slew stuff

/**
 * @brief  Set slew min power
 * @param  minPower min power
 * @return void
*/
void PID::setSlewMinPower(double minPower){
    slewMinPower = minPower;
}

/**
 * @brief  Set slew distance
 * @param  distance distance
 * @return void
*/
void PID::setSlewDistance(double distance){
    slewDistance = distance;
}

/**
 * @brief  Initialize slew
 * @param  slew slew struct
 * @param  slewOn slew on or off
 * @param maxSpeed max speed
 * @param target target in inches
 * @param current current value
 * @param start start postion
 * @param isBackwards is robot moving backwards?
*/
void PID::slewInit( bool slewOn, int maxSpeed, double target, double current, double start, bool isBackwards, int ticks_per_inch){
    slew.enabled = slewOn;
    slew.max_speed = maxSpeed;
    slew.tickPerInch = ticks_per_inch;
   
    slew.sign = util::sign(target - current);
    slew.x_intercept = start + ((slew.sign * slewDistance)* slew.tickPerInch);
    slew.y_intercept = slew.sign * slew.max_speed;

    slew.slope = ((slew.sign * slewMinPower) - slew.y_intercept) / (slew.x_intercept - 0 - start);  // y2-y1 / x2-x1

}

/**
 * @brief  Calculate slew
 * @param  slew slew struct
 * @param  current current value
 * @return void
*/
double PID::slewCalc( double current){
    if(slew.enabled){
        slew.error = slew.x_intercept - current;
        
        //when sign flip slew is done
        if(util::sign(slew.error) != slew.sign){
            slew.enabled = false;
        }
        else{
            return (slew.slope * slew.error + slew.y_intercept);
        }

    }
    return slew.max_speed;
}
