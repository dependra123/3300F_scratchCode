

#include <functional>
#include <iostream>
#include <tuple>
#include <cmath>

#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "drive.hpp"



/**
 * \brief Drive Chassis is a class that contains motors and pid functions for the drive chassis
 * \param leftMotorPorts
 * Left motor ports negative port will reverse it!
 * \param rightMotorPorts
 * Right motor ports negative port will reverse it!
 * \param imuPort
 * IMU Port
 * \param gearset
 * Gearset
*/

Drive::Drive(std::vector<int> leftMotorPorts, std::vector<int> rightMotorPorts, int imuPort, pros::motor_gearset_e gearset, double wheelDiameter)
: leftMotors {
    pros::Motor(abs(leftMotorPorts[0]), gearset, (leftMotorPorts[0] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES),
    pros::Motor(abs(leftMotorPorts[1]), gearset, (leftMotorPorts[1] < 0)? true : false, pros::E_MOTOR_ENCODER_DEGREES)
}, rightMotors {
    pros::Motor(abs(rightMotorPorts[0]), gearset, (rightMotorPorts[0] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES),
    pros::Motor(abs(rightMotorPorts[1]), gearset, (rightMotorPorts[1] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES)
}, imu_Sensor(imuPort), wheelDiameter(wheelDiameter)
{}

/**
 * \brief sets the left and right motors to a speed
 * \param leftSpeed
 * Left motor speed
 * \param rightSpeed
 * Right motor speed
 * \return void
*/
void Drive::setTank(double leftSpeed, double rightSpeed)
{
    for (int i = 0; i < leftMotors.size(); i++)
    {
        leftMotors[i].move(leftSpeed);
    }
    for (int i = 0; i < rightMotors.size(); i++)
    {
        rightMotors[i].move(rightSpeed);
    }
}

/**
 * \brief returns the average of the left motors
 * \return double
*/
double Drive::leftSensor()
{
    double sum = 0;
    for (int i = 0; i < leftMotors.size(); i++)
    {
        sum += leftMotors[i].get_position();
    }
    return sum / leftMotors.size();
}

/**
 * \brief returns the average of the right motors
 * \return double
*/
double Drive::rightSensor()
{
    double sum = 0;
    for (int i = 0; i < rightMotors.size(); i++)
    {
        sum += rightMotors[i].get_position();
    }
    return sum / rightMotors.size();
}

/**
 * \brief returns ticks per inch
 * \return double
*/
double Drive::getTickPerInch()
{
    double circumference = wheelDiameter * 3.14159265358979323846;

    double ticks_per_rev = (50.0 * (3600.0 / 200));

    return ticks_per_rev / circumference;
}

/**
 * \brief runs auton drive function
*/
void Drive::autoTask(){
    while(true){
        if(driveMode == DRIVE && (drivePID.error < 0 || drivePID.error > 0)) driveTask();
        else if(driveMode == TURN && (turnPID.error < 0 || drivePID.error > 0)) turnTask();
        else if(driveMode == SWING) swingTask();


    }
}




void Drive::twoStickDrive(int leftStick, int rightStick)
{
    for (int i = 0; i < leftMotors.size(); i++)
    {
        leftMotors[i].move(leftStick - rightStick);
    }
    for (int i = 0; i < rightMotors.size(); i++)
    {
        rightMotors[i].move(leftStick + rightStick);
    }
}

/**
 * \brief calibrates all sensors
 * \example calibrateAllSensor();
 * \return void
 *
*/
void Drive::calibrateAllSensor()
{
    imu_Sensor.reset();
    for (int i = 0; i < leftMotors.size(); i++)
    {
        leftMotors[i].tare_position();
    }
    for (int i = 0; i < rightMotors.size(); i++)
    {
        rightMotors[i].tare_position();
    }
}


void Drive::assignPID(PID* pidObject, PID::constants pidConstants){
    pidObject-> pidConstants = pidConstants;
}

/**
 * \brief Drives the robot to a target in a straight line
 * \param target
 * Target in inches
 * \param maxSpeed
 * Max speed
*/

void Drive::drive(double target, double maxSpeed, bool slewToggle = false,bool headingToggle = true){
    drivePID.target = target;

    heading_toggle = headingToggle;

    bool isBackwards;

    l_start = leftSensor();
    r_start = rightSensor();

    //encoder target values
    l_target_encoder = l_start + (target * getTickPerInch());
    r_target_encoder = r_start + (target * getTickPerInch());



    if(l_start > l_target_encoder && r_start > l_target_encoder){
        auto consts = backward_DrivePID.pidConstants;
        assignPID(&l_PID, consts);
        assignPID(&r_PID, consts);
        isBackwards = true;
    } 
    else {
        auto consts = drivePID.pidConstants;
        assignPID(&l_PID, consts);
        assignPID(&r_PID, consts);
        isBackwards = false;
    }

    l_PID.target = l_target_encoder;
    r_PID.target = r_target_encoder;

    /**
     * TODO: add slew
    */


    //run PID
    driveMode.store(DRIVE);
}


