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
    intakeMotor.move_velocity(-200);
    indexerMotor.move_velocity(200);
}
void stopIntake(){
    intakeMotor.move(0);
    indexerMotor.move(0);
}
void runIndexer(){
    indexerPrime.set_value(1);
    indexerMotor.move_velocity(-190);
}
void stopIndexer(){
    indexerPrime.set_value(0);
    indexerMotor.move_velocity(0);
}
void runFlywheel(int flyWheelSpeed){
    flyWheelMotors[0].move_velocity(flyWheelSpeed);
    flyWheelMotors[1].move_velocity(flyWheelSpeed);
}
void stopFlywheel(){
    flyWheelMotors[0].move_velocity(200);
    flyWheelMotors[1].move_velocity(200);

}

/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
    int farShoot = 450;
    int nearShoot = 360;
    
    runFlywheel(nearShoot);
    chassis.turn(100, 110);
    chassis.waitUntilSettled();
    chassis.drive(4, 110);
    chassis.waitUntilSettled();
    pros::delay(500);
    runIndexer();
    pros::delay(1000);
    stopIndexer();
    stopFlywheel();
    
    chassis.turn(-145, 110);
    chassis.waitUntilSettled();
    chassis.drive(6, 110);
    runIntake();
    chassis.waitUntilSettled();
    pros::delay(1000);

    
    runFlywheel(430);
    chassis.turn(145, 110);
    chassis.waitUntilSettled();
    pros::delay(1000);
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();

    chassis.turn(100, 110);
    chassis.waitUntilSettled();
    chassis.drive(-10, 110);
    chassis.waitUntilSettled();
    chassis.turn(-45, 110);
    chassis.waitUntilSettled();

    chassis.drive(-2, 110);
    
    chassis.waitUntilSettled();
    indexerMotor.move_absolute(360*10, 200);
    while(indexerMotor.get_actual_velocity() > 0){
        pros::delay(10);
    }
    
    stopIntake();

    //get 3 stack
    chassis.drive(2, 110);
    chassis.waitUntilSettled();
    runIntake();
    chassis.drive(3, 70);
    chassis.waitUntilSettled();
    pros::delay(1000);
    stopIntake();

    //get roller
    chassis.drive(2, 110);
    chassis.waitUntilSettled();
    chassis.turn(90, 110);
    chassis.waitUntilSettled();
    chassis.drive(-2, 110);
    chassis.waitUntilSettled();
    indexerMotor.move_absolute(360*10, 200);
    while(indexerMotor.get_actual_velocity() > 0){
        pros::delay(10);
    }
    
    stopIntake();

    //shoot
    chassis.drive(2, 110);
    chassis.waitUntilSettled();
    runFlywheel(farShoot);
    chassis.turn(0, 110);
    chassis.waitUntilSettled();
    chassis.drive(2, 110);
    chassis.waitUntilSettled();
    chassis.turn(10, 110);
    chassis.waitUntilSettled();
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();

    //get 3 line
    chassis.turn(45, 110);
    chassis.waitUntilSettled();
    runIntake();
    chassis.drive(10, 120, true);
    chassis.waitUntilSettled();
    pros::delay(1000);
    stopIntake();

    //shoot
    chassis.turn(-85, 110);
    chassis.waitUntilSettled();
    runFlywheel(nearShoot);
    chassis.drive(2, 110);












 
}
