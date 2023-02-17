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