

#include <functional>
#include <iostream>
#include <tuple>

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