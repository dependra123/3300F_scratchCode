#include "main.h"

int MAX_SPEED = 100;
int TURN_SPEED = 90;

/**
 * @brief  Sets Default PID Constants for all drive PID's
*/
void setPIDConstants(){

    chassis.assignPID(&chassis.headingPID, {3, 0.0, 5.0, 0.0});
    chassis.assignPID(&chassis.drivePID, {2, 0.2, 16, 6});
    chassis.assignPID(&chassis.backward_DrivePID, {4, 0.2, 10, 6});
    chassis.assignPID(&chassis.turnPID, {6, 0.003, 35, 15});
    chassis.l_PID.setSlewDistance({7, 7});
    chassis.r_PID.setSlewDistance({7, 7});
    chassis.l_PID.setSlewMinPower({85, 80});
    chassis.r_PID.setSlewMinPower({85, 80});
}

void runIntake(){
    intakeMotor.move(127);
    indexerMotor.move(127);
}
void runIndexer(){
    indexerMotor.move(-120);
}


/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
       pros::lcd::print(4, "drivePID kp %f", [&] {chassis.drivePID.getConstants().kP;});
    pros::lcd::print(1, "drivePID ki %f", chassis.drivePID.getConstants().kI);
    pros::lcd::print(2, "drivePID kd %f", chassis.drivePID.getConstants().kD);


    // chassis.turn(90, TURN_SPEED);
    // chassis.waitUntilSettled();
    // chassis.turn(0, MAX_SPEED);
    // chassis.waitUntilSettled();
    // chassis.turn(-90, TURN_SPEED);
    // chassis.waitUntilSettled();
    // chassis.drive(-24, MAX_SPEED, true, false);
    // chassis.waitUntilSettled();
    chassis.drive(24, MAX_SPEED, true);
    chassis.waitUntilSettled();
    chassis.drive(-24, MAX_SPEED, true);
    chassis.waitUntilSettled();
    chassis.turn(0, TURN_SPEED);
    chassis.waitUntilSettled();
 
}
