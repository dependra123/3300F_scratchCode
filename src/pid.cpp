#include "main.h"

double PID::compute(double current) {
    error = target - current;
    derivative = error - lastError;
    int error_sign;
    int prev_error_sign;

    if(error > 0)
        error_sign = 1;
    else if(error < 0)
        error_sign = -1;
    else
        error_sign = 0;

    if(lastError > 0)
        prev_error_sign = 1;
    else if(lastError < 0)
        prev_error_sign = -1;
    else
        prev_error_sign = 0;
    

    if (pidConstants.kI != 0) {
        if (fabs(error) < pidConstants.start_i)
        integral += error;

        if(error_sign != prev_error_sign)
        integral = 0;
    }

    output = (error * pidConstants.kP) + (integral * pidConstants.kI) + (derivative * pidConstants.kD);

    lastError = error;

    return output;
}