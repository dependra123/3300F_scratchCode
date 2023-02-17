

#include "main.h"



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
 * \brief resets all PID targets
 * \return void
*/
void Drive::resetPIDTargets()
{
    headingPID.target = 0;
    drivePID.target = 0;
    backward_DrivePID.target = 0;
    turnPID.target = 0;
}

/**
 * \brief sets break mode for all drive motors
 * \param mode pros::motor_brake_mode_e
 * \return void
*/
void Drive::setDriveBrakeMode(pros::motor_brake_mode_e mode)
{
    for (int i = 0; i < leftMotors.size(); i++)
    {
        leftMotors[i].set_brake_mode(mode);
    }
    for (int i = 0; i < rightMotors.size(); i++)
    {
        rightMotors[i].set_brake_mode(mode);
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
// void Drive::autoTask(){
    
//     while(true){
//         if(driveMode.load()== DRIVE && (drivePID.error < 0 || drivePID.error > 0)) driveTask();
//         //else if(driveMode == TURN && (turnPID.error < 0 || turnPID.error > 0)) turnTask();
//         //else if(driveMode.load() && (swingPID.error <0 || swingPID.error>0)) swingTask();

//          pros::c::task_delay(15);
        
//     }
// }






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
    pidObject-> setConstants(pidConstants);
}

/**
 * \brief Drives the robot to a target in a straight line
 * \param target
 * Target in inches
 * \param maxSpeed
 * int Max speed
 * \param slewToggle
 * bool Slew Toggle
 * \param headingToggle
 * bool Heading Toggle
 * \return void
*/
void Drive::drive(double target, int max_Speed, bool slewToggle,bool headingToggle){
    drivePID.target = target;
    maxSpeed = max_Speed;

    drivePID.error = drivePID.target - (leftSensor() + rightSensor()) / 2;

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
        
        
        assignPID(&l_PID, drivePID.getConstants());
        assignPID(&r_PID, drivePID.getConstants());

        isBackwards = false;
    }

    l_PID.target = l_target_encoder;
    r_PID.target = r_target_encoder;

    pros::lcd::print(0, "l: %f", l_PID.pidConstants.kP);
    /**
     * TODO: add slew
    */
    

    //run PID
    
}



/**
 * \brief Drive task with heading correction
 * \return void
*/
void Drive::driveTask(){
    pros::lcd::print(0, "l: %f", l_PID.pidConstants.kP);
    pros::lcd::print(1, "here");

    l_PID.compute(leftSensor());
    r_PID.compute(rightSensor());
    headingPID.compute(imu_Sensor.get_heading());

    /**
     * TODO: compute slew and clip right and left pid to it
    */

    double gyroCorrection = heading_toggle ? headingPID.output : 0;

    l_PID.output = util::clamp(l_PID.output, -127, 127);
    r_PID.output = util::clamp(r_PID.output, -127, 127);
   

    setTank(l_PID.output + gyroCorrection, r_PID.output - gyroCorrection);
}