
#include <functional>
#include <iostream>
#include <tuple>
#include<algorithm> // for copy() and assign() 
#include<iterator> // for back_inserter


#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "drive.hpp"




int Drive::Chassis(std::vector<int> leftMotorPorts, std::vector<int> rightMotorPorts, pros::Imu IMU, pros::motor_gearset_e gearset)
{
    // get abs value of motor ports
    static int leftport1 = abs(leftMotorPorts[0]);
    static int leftport2 = abs(leftMotorPorts[1]);
    static int rightport1 = abs(rightMotorPorts[0]);
    static int rightport2 = abs(rightMotorPorts[1]);

    const pros::Motor leftMotor1(leftport1, gearset, (leftMotorPorts[0] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES);
    const pros::Motor rightMotor1(rightport1, gearset, (rightMotorPorts[0] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES);
    const pros::Motor leftMotor2(leftport2, gearset, (leftMotorPorts[1] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES);
    const pros::Motor rightMotor2(rightport2, gearset, (rightMotorPorts[1] < 0) ? true : false, pros::E_MOTOR_ENCODER_DEGREES);

    

    std::vector<pros::Motor> left_motors;
    std::vector<pros::Motor> right_motors;
    
    left_motors.push_back(leftMotor1);
    left_motors.push_back(leftMotor2);
    right_motors.push_back(rightMotor1);
    right_motors.push_back(rightMotor2);


    std::copy(left_motors.begin(), left_motors.end(), std::back_inserter(leftMotors));
    std::copy(right_motors.begin(), right_motors.end(), std::back_inserter(rightMotors));

    
   
    return 0;
}
