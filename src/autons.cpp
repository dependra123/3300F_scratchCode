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
    chassis.l_PID.setSlewMinPower({90, 90});
    chassis.r_PID.setSlewMinPower({90, 90});
}

void runIntake(){
    intakeMotor.move(-127);
    indexerMotor.move(127);
}
void runIndexer(){
    indexerPrime.set_value(1);
    indexerMotor.move_velocity(-190);
}
void stopIndexer(){
    indexerPrime.set_value(0);
    indexerMotor.move_velocity(0);
}


/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
    
    flyWheelActive = true;
    flyWheelSpeed = 360;

    chassis.turn(100, 110);
    chassis.waitUntilSettled();
    pros::delay(1500);
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    
    flyWheelActive = false;

    chassis.drive(-20, 110, true);
    chassis.headingPID.target = chassis.headingPID.target - 5;
    chassis.waitUntilSettled();

    //rotate indexder motor a spesifc amount of times
    indexerMotor.move_relative(360*6, 200);
    while(indexerMotor.get_actual_velocity() != 0){
        pros::delay(20);
    }
    indexerMotor.move_velocity(0);

    chassis.drive(5, 120);
    chassis.waitUntilSettled();
    chassis.turn(-90, 110);
    chassis.waitUntilSettled();
    chassis.drive(-6, 110);
    chassis.waitUntilSettled();

    //rotate indexder motor a spesifc amount of times
    indexerMotor.move_relative(360*6, 200);
    while(indexerMotor.get_actual_velocity() != 0){
        pros::delay(20);
    }

    chassis.drive(8, 100);
    runIntake();
    chassis.waitUntilSettled();
    

    




 
}
