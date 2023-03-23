#include "main.h"

/** \file declare.cpp
 * \brief This file contains the declarations for the general functions
 *
 * This file contains the functions as well as the declarations of motors and sensors
 *
 *  
*/

//Motor Declarations
pros::Motor intakeMotor(15, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor indexerMotor(13, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
std::vector<pros::Motor> flyWheelMotors{
    pros::Motor(9, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES),
    pros::Motor(10, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES)
};

//pnematic declarations
pros::ADIDigitalOut indexerPrime(1);
pros::ADIDigitalOut endgame(2);

//flywheel variables
std::atomic<int> flyWheelSpeed(0);
std::atomic<double> flyWheelkV(0.0001);
std::atomic<bool> flyWheelActive(false);


//Function Declarations
PID flyWheelPID;

/**
 * \brief
 * This code spins the flywheel, using a PID loop, at a target speed, which is set by the user, and read by the robot, using the flyWheelSpin task, which is running at the same time as the flyWheelSpin task. 
 *  The flyWheelSpin task is run by the flyWheelSpin button on the controller, which toggles the flyWheelActive variable, which is used by the flyWheelSpin task to determine whether or not to spin the flywheel.
 * \param speed
 * speed of flywheel (use flyWheelSpeed variable)
 * \param kP
 * proportional constant (use flyWheelkP variable)
 * \param kV
 * feedforward constant (use flyWheelkV variable)
 * \param active
 * bool to turn on and off ( use flyWheelActive variable)
 * 

*/
void flyWheelSpin(){
    flyWheelPID.pidConstants = {100, 0, 0, 0};
    
    flyWheelPID.compute((flyWheelMotors[0].get_actual_velocity() + flyWheelMotors[1].get_actual_velocity())/ 2);
    flyWheelMotors[0].move_velocity(flyWheelPID.output);
    flyWheelMotors[1].move_velocity(flyWheelPID.output);
        
}

