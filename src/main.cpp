#include "main.h"
#include "autoSelect/selection.h"


using namespace std;

/**
 * Drive Chassis is a class that contains motors and pid functions for the drive chassis
 * 
 * Motors are stored in a vector of motors
 * Look at drive.hpp and drive.cpp for more info 
*/

Drive chassis(
	// Left Chassis Ports (negative port will reverse it!)
	{14, 11}
	// Right Chassis Ports (negative port will reverse it!)
	,{-16, -17},

	// IMU Port
	12,
	pros::E_MOTOR_GEARSET_18,
	// Wheel Diameter
	4.125

);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
	pros::lcd::initialize();
	chassis.calibrateAllSensor();
	pros::delay(1000);

	flyWheelActive = false;
	flyWheelSpeed = 360;
	flyWheelkV = 2000;
	pros::Task t_Autontask([&] { chassis.autoTask(); }, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "AutonTask");
	chassis.driveMode = NONE;
	//pros::Task t_FlywheelTask([&]{flyWheelSpin();}, "FlywheelTask");
	//selector::init();


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	
	chassis.resetPIDTargets();
	setPIDConstants();
	chassis.setDriveBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	pros::delay(100);

	selector::init();
	//rightSideRoller(127);
	flyWheelMotors[1].set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	flyWheelMotors[0].set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	flyWheelMotors[0].move_velocity(200);
	flyWheelMotors[1].move_velocity(200);
			

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	endgame.set_value(0);	
	bool indexerActive = false;
	double curveConst = 19;
	int flyWheelSpeed = 370;

	//autonomous();

	// // left stick modified
	// int leftStick = (exp(-(curveConst/10)) + exp((abs(master.get_analog(ANALOG_LEFT_Y)) - 127) /10) * (1 - exp(-(curveConst/10))))* master.get_analog(ANALOG_LEFT_Y);
	
	// // right stick modified
	// int rightStick = (exp(-(curveConst/10)) + exp((abs(master.get_analog(ANALOG_RIGHT_X)) - 127) /10) * (1 - exp(-(curveConst/10))))* master.get_analog(ANALOG_RIGHT_X);

	// Main driver control loop
	while (true) {
		chassis.twoStickDrive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_X));

		
		if (master.get_digital(DIGITAL_L1)) {
			 flyWheelMotors[0].move_velocity(flyWheelSpeed);
			  flyWheelMotors[1].move_velocity(flyWheelSpeed);
		}
		else {
			flyWheelMotors[0].move_velocity(200);
			  flyWheelMotors[1].move_velocity(200);
		}
		

		
		if (master.get_digital(DIGITAL_L2)) {
			indexerActive = true;
			indexerMotor.move_velocity(-200);
			indexerPrime.set_value(1);
		}
		else {
			indexerActive = false;
			indexerMotor.move_velocity(0);
			indexerPrime.set_value(0);
		}

		if (master.get_digital(DIGITAL_R1)) {
			intakeMotor.move_velocity(200);
			if(!indexerActive) {
				indexerMotor.move_velocity(200);
			}
		}
		else if (master.get_digital(DIGITAL_R2)) {
			intakeMotor.move_velocity(-200);
			

		}
		else {
			intakeMotor.move_velocity(0);
			if(!indexerActive) {
				indexerMotor.move_velocity(0);
			}
		}

		if (master.get_digital(DIGITAL_B) && !master.get_digital(DIGITAL_RIGHT)) {
			flyWheelMotors[1].set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			flyWheelMotors[0].set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			flyWheelMotors[0].move_velocity(0);
			flyWheelMotors[1].move_velocity(0);
			endgame.set_value(1);
		}
		
		
		

		pros::delay(10);
	}
	
}
