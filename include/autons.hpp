#pragma once

#include "drive.hpp"

/// @brief  drive chassis
extern Drive chassis;



/**
 * @brief  Sets Default PID Constants for all drive PID's
 *
*/void setPIDConstants();

//auton Declarations

void rightSideRoller(int color);
void leftSideRoller(int color);
void winPoint(int color);
void skills();

