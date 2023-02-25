

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
    return leftMotors[0].get_position();
}

/**
 * \brief returns the average of the right motors
 * \return double
*/
double Drive::rightSensor()
{
   
    return rightMotors[0].get_position();
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
        if(driveMode.load()== DRIVE) driveTask();
        else if(driveMode.load() == TURN) turnTask();
        //else if(driveMode.load() && (swingPID.error <0 || swingPID.error>0)) swingTask();

         pros::c::task_delay(15);
        
    }
}






void Drive::twoStickDrive(int leftStick, int rightStick)
{
    rightMotors[0] =( leftStick - rightStick)* 1.6;
    rightMotors[1] =( leftStick - rightStick)* 1.6;

    leftMotors[0] = (leftStick + rightStick)*1.6;
    leftMotors[1] = (leftStick + rightStick) * 1.6;


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
    pros::delay(100);
    for (int i = 0; i < leftMotors.size(); i++)
    {
        leftMotors[i].tare_position();
        pros::delay(100);
    }
    for (int i = 0; i < rightMotors.size(); i++)
    {
        rightMotors[i].tare_position();
        pros::delay(100);
    }
    pros::delay(100);
    pros::Controller temp = pros::Controller(pros::E_CONTROLLER_MASTER);
    temp.rumble(".");
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
    l_PID.slewInit(slewToggle, maxSpeed, target, l_target_encoder, l_start, isBackwards, getTickPerInch());
    r_PID.slewInit(slewToggle, maxSpeed, target, r_target_encoder, r_start, isBackwards, getTickPerInch()); 

    driveMode = DRIVE;

    
}



/**
 * \brief Drive task with heading correction
 * \return void
*/
void Drive::driveTask(){
    pros::lcd::print(0, "l: %f", l_PID.pidConstants.kP);
    pros::lcd::print(1, "target: %f", l_PID.target);

    l_PID.compute(leftSensor());
    r_PID.compute(rightSensor());
    headingPID.compute(imu_Sensor.get_heading());

    /**
     * TODO: compute slew and clip right and left pid to it
    */

    double gyroCorrection = heading_toggle ? headingPID.output : 0;

    double l_slewOutput = l_PID.slewCalc(leftSensor());
    double r_slewOutput = r_PID.slewCalc(rightSensor());

    l_PID.output = util::clamp(l_PID.output, -l_slewOutput, l_slewOutput);
    r_PID.output = util::clamp(r_PID.output, -r_slewOutput, r_slewOutput);   

    setTank(l_PID.output + gyroCorrection, r_PID.output - gyroCorrection);
}
/**
 * \brief Turns the robot to a target
 * \param target in degrees
 * \param maxSpeed
 * \return void
*/
void Drive::turn(double target, int max_Speed){
    
    turnPID.target = target;
    maxSpeed = max_Speed;
    headingPID.target = target;

    if(target < 0){
        imu_Sensor.set_heading(abs(target));
        turnPID.target = 0;
        headingPID.target = 0;
        pros::delay(100);
        
    }

    turnPID.compute(imu_Sensor.get_heading());
    
   
    driveMode = TURN;


}

/**
 * \brief Turn task
 * \return void
*/
void Drive::turnTask(){
    turnPID.compute(imu_Sensor.get_heading());

    turnPID.output = util::clamp(turnPID.output, -maxSpeed, maxSpeed);
    


    double gyroCorrection = turnPID.output;

    if(turnPID.pidConstants.kI!=0 &&(fabs(turnPID.target) > turnPID.pidConstants.start_i && fabs(turnPID.error) < turnPID.pidConstants.start_i)){
        gyroCorrection = util::clamp(gyroCorrection, -turnMin, turnMin);
    }

    setTank(gyroCorrection, -gyroCorrection);
}
/**
 * \brief waits until the robot has reached its target
 * \return void
*/
void Drive::waitUntilSettled(){
    //check if drive motors are moving
    pros::delay(1000);
    while(fabs(leftMotors[0].get_actual_velocity()) > 5 || fabs(rightMotors[0].get_actual_velocity()) > 5){
        pros::c::task_delay(250);
    }
}