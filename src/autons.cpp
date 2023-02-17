#include "main.h"

int MAX_SPEED = 100;
int TURN_SPEED = 90;

/**
 * @brief  Sets Default PID Constants for all drive PID's
*/
void setPIDConstants(){

    chassis.assignPID(&chassis.headingPID, {0, 0.0, 0.0, 0.0});
    chassis.assignPID(&chassis.drivePID, {0.5, 0, 0.0, 0});
    chassis.assignPID(&chassis.backward_DrivePID, {0.5, 0.0, 0.0, 0.0});
    chassis.assignPID(&chassis.turnPID, {0.5, 0.0, 0.0, 0.0});
    chassis.l_PID.setSlewDistance({7, 7});
    chassis.r_PID.setSlewDistance({7, 7});
    chassis.l_PID.setSlewMinPower({80, 80});
    chassis.r_PID.setSlewMinPower({80, 80});
}

/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
       pros::lcd::print(4, "drivePID kp %f", [&] {chassis.drivePID.getConstants().kP;});
    pros::lcd::print(1, "drivePID ki %f", chassis.drivePID.getConstants().kI);
    pros::lcd::print(2, "drivePID kd %f", chassis.drivePID.getConstants().kD);


    
    chassis.drive(15, MAX_SPEED, true);
    chassis.waitUntilSettled();
    chassis.drive(-10, MAX_SPEED, true);
    chassis.waitUntilSettled();
    chassis.turn(90, TURN_SPEED);
    chassis.waitUntilSettled();
 
    //print to brain 


    
}
