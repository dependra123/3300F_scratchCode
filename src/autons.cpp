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

void runIntake(){
    intakeMotor.move_velocity(200);
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

void rollor(){
    indexerMotor.move_velocity(200);
}

/**
 * @brief  Right Side Roller Auton 
 * @param  color 0 for red 1 for blue
*/
void rightSideRoller(int color){
    int farShoot = 40;
    int nearShoot = 340;
    
    runFlywheel(nearShoot);
    chassis.turn(103, 110);
    chassis.waitUntilSettled();
    
    runIndexer();
    pros::delay(2000);
    stopIndexer();
    // for(int i = 0; i < 7; i++){
    //     chassis.drive(-5, 110);
    //     chassis.waitUntilSettled();
    //     pros::delay(1000);
    //     runIntake();
    //     chassis.drive(5, 110);
    //     chassis.waitUntilSettled();
    //     pros::delay(2000);
    //     runIndexer();
    //     pros::delay(1000);
    //     stopIndexer();

    // }
    stopFlywheel();
    flyWheelMotors[0].move_velocity(0);
    flyWheelMotors[1].move_velocity(0);



    chassis.drive(-14, 110, true);
    chassis.waitUntilSettled();
    chassis.turn(-2, 110);
    chassis.waitUntilSettled();
    rollor();
    

    chassis.drive(-3, 110);
    chassis.waitUntilSettled();
    pros::delay(500);
    stopIntake();
    runIntake();
    // chassis.turn(180, 110);
    // chassis.waitUntilSettled();
    chassis.drive(11, 110, true);
    chassis.waitUntilSettled();
    chassis.turn(83, 110);
    chassis.waitUntilSettled();
    chassis.drive(-11, 110);
    chassis.waitUntilSettled();
    rollor();
    pros::delay(1000);

    stopIntake();
    pros::delay(1000);

    chassis.turn(250,110);
    chassis.waitUntilSettled();
    chassis.drive(-505, 120);
    chassis.waitUntilSettled();
    chassis.turn(-45, 110);
    chassis.waitUntilSettled();
    chassis.drive(-3, 100);
    rollor();
    pros::delay(1000);
    stopIntake();

    chassis.drive(10, 100);
    chassis.waitUntilSettled();
    chassis.turn(270, 110);
    chassis.waitUntilSettled();
    chassis.drive(-5, 100);
    rollor();
    pros::delay(1000);
    stopIntake();

    //go to corner
    chassis.turn(180, 110);
    chassis.waitUntilSettled();
    chassis.drive(10, 110);
    chassis.waitUntilSettled();
    chassis.turn(-45, 110);
    chassis.waitUntilSettled();

    endgame.set_value(1);




    







    
  

    
    
    // //get roller
   // chassis.turn(90, 110);
    
    // // indexerMotor.move_absolute(360*10, 200);
    // // while(indexerMotor.get_actual_velocity() > 0){
    // //     pros::delay(10);
    // // }
    
    // // stopIntake();

    // //shoot
    // chassis.drive(5, 120);
    // chassis.waitUntilSettled();
    // runFlywheel(farShoot);
    // // chassis.turn(10, 110);
    // // chassis.waitUntilSettled();
    // chassis.drive(2, 110);
    // chassis.waitUntilSettled();
    // chassis.turn(10, 110);
    // chassis.waitUntilSettled();
    // runIndexer();
    // pros::delay(1500);
    // stopIndexer();
    // stopFlywheel();

    // //get 3 line
    // chassis.turn(45, 110);
    // chassis.waitUntilSettled();
    // runIntake();
    // chassis.drive(10, 120, true);
    // chassis.waitUntilSettled();
    // pros::delay(1000);
    // stopIntake();

    // //shoot
    // chassis.turn(-85, 110);
    // chassis.waitUntilSettled();
    // runFlywheel(nearShoot);
    // chassis.drive(2, 110);
    // chassis.waitUntilSettled();
    // runIndexer();
    // pros::delay(1500);
    // stopIndexer();
    // stopFlywheel();


    // //get 3 stack
    // //ur setting the rotation not like the amount it should turn kinda like a compas unless u do a negativ
    // //then it reset to zero at ending postion
    // //say smth if u red that
    // chassis.turn(85,110);
    // chassis.waitUntilSettled();
    // runIntake();
    // chassis.drive(10, 75, true);
    // chassis.waitUntilSettled();
    // pros::delay(1000);
    // stopIntake();
    // runFlywheel(farShoot);
    // chassis.turn(-195, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(5, 110);
    // chassis.headingPID.target = 10;
    // chassis.waitUntilSettled();
    // runIndexer();
    // pros::delay(1500);
    // stopIndexer();
    // stopFlywheel();



    // chassis.headingPID.target = 0;
    // chassis.waitUntilSettled();
    // chassis.turn(-5, 110);
    // chassis.waitUntilSettled();
    //    //pointing backwards
    // chassis.drive(-15, 110, true);
    // chassis.waitUntilSettled();
    // chassis.turn(-90, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(-3, 110);
    // chassis.waitUntilSettled();
    // //rollor
    // indexerMotor.move_absolute(360*10, 200);
    // while(indexerMotor.get_actual_velocity() > 0){
    //     pros::delay(10);
    // }
    // chassis.drive(5, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(3, 70);
    // chassis.waitUntilSettled();
    // chassis.turn(90, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(-5, 110);
    // chassis.waitUntilSettled();
    // indexerMotor.move_absolute(360*10, 200);
    // while(indexerMotor.get_actual_velocity() > 0){
    //     pros::delay(10);
    // }
 


    // chassis.drive(2.5, 110);
    // chassis.waitUntilSettled();
    // chassis.turn(90, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(15, 110, true);
    // chassis.waitUntilSettled();
    // runFlywheel(nearShoot);
    // chassis.turn(10, 110);
    // chassis.waitUntilSettled();
    // runIndexer();
    // pros::delay(1500);
    // stopIndexer();
    // stopFlywheel();


    // //get line of 3
    // chassis.turn(135, 110);
    // chassis.waitUntilSettled();
    // runIntake();
    // chassis.drive(15, 120, true);
    // chassis.waitUntilSettled();
    // chassis.turn(85, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(10, 110);
    // chassis.waitUntilSettled();
    // runFlywheel(nearShoot + 20);
    // pros::delay(1000);
    // stopIntake();
    // chassis.turn(-85, 110);
    // chassis.waitUntilSettled();
    // runIndexer();
    // pros::delay(1500);
    // stopIndexer();
    // stopFlywheel();

    // //get 3 stack
    // chassis.turn(85, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(7, 110);
    // chassis.waitUntilSettled();
    // runIntake();
    // chassis.drive(5, 90);
    // chassis.waitUntilSettled();
    // pros::delay(1000);
    // stopIntake();
    // chassis.turn(-105, 110);
    // runFlywheel(nearShoot);

    // chassis.waitUntilSettled();
    // chassis.drive(5, 110);
    // chassis.headingPID.target = 10;
    // chassis.waitUntilSettled();
    // runIndexer();
    // pros::delay(1500);
    // stopIndexer();
    // stopFlywheel();



    // //FINAIL PART 
    // flyWheelMotors[0].set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // flyWheelMotors[1].set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    // //stop flywheel
    // flyWheelMotors[0].move_velocity(0);
    // flyWheelMotors[1].move_velocity(0);
    // //move to corner of field
    // chassis.drive(-5, 110);
    // chassis.waitUntilSettled();
    // chassis.turn(-60, 110);
    // chassis.waitUntilSettled();
    // chassis.drive(-20, 110, true);
    // chassis.waitUntilSettled();
    // chassis.turn(-30, 110);
    // chassis.waitUntilSettled();
    // //shoot endgame
    // endgame.set_value(1);
    // pros::delay(500);
    // chassis.drive(2.5, 127);
    
    // chassis.waitUntilSettled();

}
