#include  "api.h"
#include <iostream>
#include <atomic>

extern pros::Motor intakeMotor;

/**
 * indexer motor also poweres roller
 * and is part of intake
*/
extern pros::Motor indexerMotor;
extern std::vector<pros::Motor> flyWheelMotors;
extern pros::ADIDigitalOut indexerPrime;
extern pros::ADIDigitalOut endgame;

extern std::atomic <int> flyWheelSpeed;

extern std::atomic <double> flyWheelkV;
extern std::atomic <bool> flyWheelActive;


void flyWheelSpin();
