#include "main.h"

int MAX_SPEED = 100;

/**
 * @brief  Sets Default PID Constants for all drive PID's
*/
void setPIDConstants(){
    chassis.assignPID(&chassis.headingPID, {0.0, 0.0, 0.0, 0.0});
    chassis.assignPID(&chassis.drivePID, {0.5, 0.0, 0.0, 0.0});
    chassis.assignPID(&chassis.backward_DrivePID, {0.5, 0.0, 0.0, 0.0});
    chassis.assignPID(&chassis.turnPID, {0.5, 0.0, 0.0, 0.0});
    
}

/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
    chassis.drive(5, MAX_SPEED);

    pros::lcd::print(4, "drivePID kp %f", [&] {chassis.drivePID.getConstants().kP;});
    pros::lcd::print(1, "drivePID ki %f", chassis.drivePID.getConstants().kI);
    pros::lcd::print(2, "drivePID kd %f", chassis.drivePID.getConstants().kD);


    while(chassis.drivePID.error > 0 || chassis.drivePID.error < 0){
        chassis.driveTask();
        pros::c::task_delay(15);
    }
    //print to brain 


    
}
