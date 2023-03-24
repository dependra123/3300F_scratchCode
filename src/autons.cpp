#include "main.h"
//nerd fr
int MAX_SPEED = 100;
int TURN_SPEED = 90;

/**
 * @brief  Sets Default PID Constants for all drive PID's
*/
void setPIDConstants(){

    chassis.assignPID(&chassis.headingPID, {0.3, 0.0, 0.0, 0.0});
    chassis.assignPID(&chassis.drivePID, {2, 0.2, 16, 6});
    chassis.assignPID(&chassis.backward_DrivePID, {4, 0.2, 10, 6});
    chassis.assignPID(&chassis.turnPID, {6, 0.003, 35, 15});
    chassis.assingTimeouts(&chassis.turnPID, {5, 100, 15, 500, 2000});
    chassis.assingTimeouts(&chassis.drivePID, {3, 500, 5, 1000, 6000 });
    chassis.l_PID.setSlewDistance({7, 7});
    chassis.r_PID.setSlewDistance({7, 7});
    chassis.l_PID.setSlewMinPower({90, 90});
    chassis.r_PID.setSlewMinPower({90, 90});
}
