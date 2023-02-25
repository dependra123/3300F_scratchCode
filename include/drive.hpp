
#include <functional>
#include <iostream>
#include <tuple>
#include <cmath>
#include <atomic>

#include "pid.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"

enum autonDriveMode {DRIVE, TURN, SWING, NONE};
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

        bool heading_toggle = true;


        // auton variables
        PID headingPID;
        PID drivePID;
        PID backward_DrivePID;
        PID turnPID;
        PID swingPID;

        //drive only pid    
        PID l_PID;
        PID r_PID;

        double turnMin;
        double swingMin;
        
        //auton drive mode
        std::atomic<autonDriveMode> driveMode;
        double l_start;
        double r_start;
        double l_target_encoder;
        double r_target_encoder;
        int maxSpeed;
        

        void autoTask();
        void driveTask();
        void turnTask();
        void swingTask();


        

       
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
        void resetPIDTargets();
        void setDriveBrakeMode(pros::motor_brake_mode_e brakeMode);
        void init();

        double rightSensor();
        double leftSensor();

        double getTickPerInch();


        void assignPID(PID* pidObject, PID::constants pidConstants);

        void drive(double target, int max_Speed, bool slewToggle = false,bool headingToggle = true);
        void turn(double target, int max_Speed);
        void setTank(double leftSpeed, double rightSpeed);

        void waitUntilSettled();

        
};