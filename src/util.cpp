#include "main.h"
#include <math.h>



/**
 * @brief  Get sign of a number
 * @param  x number to get sign of
 * @return 1 if positive, -1 if negative, 0 if 0
*/
int util::sign(double x){
    if(x > 0)
        return 1;
    else if(x < 0)
        return -1;
    else
        return 0;
}
/**
 * @brief  Clamp a number between a min and max
 * @param  x number to clamp
 * @param  min minimum value
 * @param  max maximum value
 * @return clamped value
*/
double util::clamp(double x, double min, double max){
    if(x > max)
        return max;
    else if(x < min)
        return min;
    else
        return x;
}


/**
 * @brief  Convert degrees to radians
 * @param  deg degrees
 * 
 * 
 * @return radians
*/
inline double util::degToRad(double deg){
    return deg * PI / 180;
   
}
/**
 * @brief  Convert radians to degrees
 * @param  rad radians
 * @return degrees
*/
inline double util::radToDeg(double rad){
    return rad * 180 / PI;
}
