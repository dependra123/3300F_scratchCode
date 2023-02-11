
#include <functional>
#include <iostream>
#include <tuple>

#include "pros/imu.hpp"
#include "pros/motors.hpp"

class Drive {
    public:
        /**
            *\param leftMotorPorts
            *\param rightMotorPorts
            *\param IMU
        */
        std::vector<pros::Motor> leftMotors ;
        std::vector<pros::Motor> rightMotors;
        pros::Imu imu;

        int Chassis(std::vector<int> leftMotorPorts, std::vector<int> rightMotorPorts, pros::Imu IMU, pros::motor_gearset_e gearset);
                

        

};