
#include <functional>
#include <iostream>
#include <tuple>

#include "pros/imu.hpp"
#include "pros/motors.hpp"


class Drive {
    public:
        /**
         * \brief motors are stored in a vector of motors
        */
        std::vector<pros::Motor> leftMotors ;
        /**
         * \brief motors are stored in a vector of motors
        */
        std::vector<pros::Motor> rightMotors;
        pros::Imu imu_Sensor;
        double wheelDiameter;
       
        /**
            *\param leftMotorPorts
            *\param rightMotorPorts
            *\param IMU
            *\param gearset
            *\param wheelDiameter
        */ 
        Drive(std::vector<int> leftMotorPorts, std::vector<int> rightMotorPorts, int imuPort, pros::motor_gearset_e gearset, double wheelDiameter);

        void twoStickDrive(int leftStick, int rightStick);
        void calibrateAllSensor();
};
