#include "main.h"


/**
 * @brief  Sets Default PID Constants for all drive PID's
 *
*/
void setPIDConstants(){
    chassis.assignPID(&chassis.headingPID, {0.5, 0.0, 0.0});
    chassis.assignPID(&chassis.drivePID, {0.5, 0.0, 0.0});
    chassis.assignPID(&chassis.turnPID, {0.5, 0.0, 0.0});
}

/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
    
}
