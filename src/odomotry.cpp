

#include <iostream>
#include <math.h>
#include "main.h"


void Odom::odomTask(){
    //initliaze all variables
    double totalBack = util::degToRad(chassis.odomPorts.ports[2].get_position()/100);
    double totalLeft = util::degToRad(chassis.odomPorts.ports[0].get_position()/100);
    double totalRight = util::degToRad(chassis.odomPorts.ports[1].get_position()/100);

    double curcumfrence = chassis.odomPorts.wheelDiameter * PI;
    //inches per degree in radians
    double ipd = curcumfrence / (2*PI);

    initTheta = PI;
    lastTheta = initTheta;
    lastPos = {0, 0};

    double deltaTheta = 0;
    std::vector<double> localOffset;

    double avgOrientation = 0;
    while(true){
        
        //This code gets the change in position of the bot in radians and adds it to the last position of the bot.
        double distBack = chassis.odomPorts.ports[2].get_position() - totalBack;
        double distLeft = chassis.odomPorts.ports[0].get_position() - totalLeft;
        double distRight = chassis.odomPorts.ports[1].get_position() - totalRight;

        //update total position
        totalRight += util::degToRad(distRight);
        totalLeft += util::degToRad(distLeft);
        totalBack += util::degToRad(distBack);

           
        // It uses the varible IPD(inches per degree) to convert the change in position from radians to inches.
        distBack *= ipd;
        distLeft *= ipd;
        distRight *= ipd;



        // This code calculates the change in heading of the robot. It does this by calculating the total movement of left and right wheel, subtracting the two values, and dividing the difference by the distance between the traking center.
        //This value is then added to the initial heading of the robot to get the final heading.

        theta = initTheta +(((totalLeft * ipd) - (totalRight * ipd)) / (chassis.odomPorts.offsets[0] + chassis.odomPorts.offsets[1]));
        deltaTheta = theta - lastTheta;

        if(deltaTheta == 0){
            //If the change in heading is 0, then the robot has only moved forward or backwards.
            // This means that the local offset is only in the y direction.
            localOffset = {distBack, distRight};
        }
        else{  
            //otherwise the robot has moved in an arc, and the local offset is calculated using the formulas below.
            double x = 2*(sin(deltaTheta/2) * (distBack / deltaTheta) + chassis.odomPorts.offsets[2]);
            double y = (distRight / deltaTheta) + chassis.odomPorts.offsets[1];
            localOffset = {x, y};
        }

        //This code calculates the average orientation of the robot during the movement.
        avgOrientation = lastTheta + deltaTheta / 2;

        //caclulate the radius of the arc the robot moved in
        double r =sqrt(pow(localOffset[0], 2) + pow(localOffset[1], 2));

        //Convert to polar coordinates so that local offset can be rotated by the average orientation 
        std::vector<double> polarCords = {r, atan2(localOffset[1] , localOffset[0])};

        //rotate the local offset by the average orientation
        polarCords[1] -= avgOrientation;
        
        /*
        convert back to cartesian coordinates and now the local offset is a global offset this means
        instead of the movments being relative to the robot, they are relative to the field.   
        */
        std::vector<double> globalOffset = {r * cos(polarCords[1]), r * sin(polarCords[1])};

        //add the global offset to the last position to get the current position
        pos = {lastPos[0] + globalOffset[0], lastPos[1] + globalOffset[1]};


        //update prev values
        lastTheta = theta;
        lastPos = pos;

        pros::delay(10);
    }
}

std::vector<double> Odom::getPos(){
    return pos;
}

void Odom::reset(){
    chassis.odomPorts.ports[0].set_position(0);
    chassis.odomPorts.ports[1].set_position(0);
    chassis.odomPorts.ports[2].set_position(0);
    initTheta = PI;
    lastTheta = initTheta;
    lastPos = {0, 0};
}

