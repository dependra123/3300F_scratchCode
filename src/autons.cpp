#include "main.h"
//nerd fr
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
    chassis.waitUntilSettled();
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();


    //get 3 stack
    //ur setting the rotation not like the amount it should turn kinda like a compas unless u do a negativ
    //then it reset to zero at ending postion
    //say smth if u red that
    chassis.turn(85,110);
    chassis.waitUntilSettled();
    runIntake();
    chassis.drive(10, 75, true);
    chassis.waitUntilSettled();
    pros::delay(1000);
    stopIntake();
    runFlywheel(farShoot);
    chassis.turn(-195, 110);
    chassis.waitUntilSettled();
    chassis.drive(5, 110);
    chassis.headingPID.target = 10;
    chassis.waitUntilSettled();
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();



    //go to other rollors
    chassis.drive(-5, 110);
    chassis.headingPID.target = 0;
    chassis.waitUntilSettled();
    chassis.turn(-75, 110);
    chassis.waitUntilSettled();
       //pointing backwards
    chassis.drive(-15, 110, true);
    chassis.waitUntilSettled();
    //finsh rollor code and get 3 stack


    //get 3 stack


    //get other rollor


    //stop here

    //shooting
    chassis.imu_Sensor.reset();
    chassis.headingPID.target = 0;

    chassis.drive(5, 110);
    chassis.waitUntilSettled();
    chassis.turn(90, 110);
    chassis.waitUntilSettled();
    chassis.drive(20, 110);
    chassis.waitUntilSettled();
    runFlywheel(nearShoot);
    chassis.turn(10, 110);
    chassis.waitUntilSettled();
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();


    //get line of 3
    chassis.turn(135, 110);
    chassis.waitUntilSettled();
    runIntake();
    chassis.drive(15, 120, true);
    chassis.waitUntilSettled();
    chassis.turn(85, 110);
    chassis.waitUntilSettled();
    chassis.drive(10, 110);
    chassis.waitUntilSettled();
    runFlywheel(nearShoot + 20);
    pros::delay(1000);
    stopIntake();
    chassis.turn(-85, 110);
    chassis.waitUntilSettled();
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();

    //get 3 stack
    chassis.turn(85, 110);
    chassis.waitUntilSettled();
    chassis.drive(7, 110);
    chassis.waitUntilSettled();
    runIntake();
    chassis.drive(5, 90);
    chassis.waitUntilSettled();
    pros::delay(1000);
    stopIntake();
    chassis.turn(-105, 110);
    runFlywheel(nearShoot);

    chassis.waitUntilSettled();
    chassis.drive(5, 110);
    chassis.headingPID.target = 10;
    chassis.waitUntilSettled();
    runIndexer();
    pros::delay(1500);
    stopIndexer();
    stopFlywheel();



    //FINAIL PART 
    flyWheelMotors[0].set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    flyWheelMotors[1].set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    //stop flywheel
    flyWheelMotors[0].move_velocity(0);
    flyWheelMotors[1].move_velocity(0);
    
    

    




 //were
 //comment here

}
