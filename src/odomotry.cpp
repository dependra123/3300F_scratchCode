

#include <iostream>
#include <math.h>
#include "main.h"



void Odom::odomTask(){

    double lastBack = util::degToRad(chassis.odomPorts.ports[2].get_position());
    double lastLeft = util::degToRad(chassis.odomPorts.ports[0].get_position());
    double lastRight = util::degToRad(chassis.odomPorts.ports[1].get_position());

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
        double distBack = chassis.odomPorts.ports[2].get_position() - lastBack;
        double distLeft = chassis.odomPorts.ports[0].get_position() - lastLeft;
        double distRight = chassis.odomPorts.ports[1].get_position() - lastRight;

        lastRight += distRight;
        lastLeft += distLeft;
        lastBack += distBack;

        distBack *= ipd;
        distLeft *= ipd;
        distRight *= ipd;

        theta = initTheta +(((lastLeft * ipd) - (lastRight * ipd)) / (2*chassis.odomPorts.wheelDiameter));
        deltaTheta = theta - lastTheta;

        if(deltaTheta == 0){
            localOffset = {distBack, distRight};
        }
        else{  
            double x = 2*(sin(deltaTheta/2) * (distBack / deltaTheta) + chassis.odomPorts.offsets[2]);
            double y = (distRight / deltaTheta) + chassis.odomPorts.offsets[1];
            localOffset = {x, y};
        }

        avgOrientation = lastTheta + deltaTheta / 2;

        double r =sqrt(pow(localOffset[0], 2) + pow(localOffset[1], 2));

        std::vector<double> polarCords = {r, atan2(localOffset[1] , localOffset[0])};
        polarCords[1] -= avgOrientation;

        std::vector<double> globalOffset = {r * cos(polarCords[1]), r * sin(polarCords[1])};

        pos = {lastPos[0] + globalOffset[0], lastPos[1] + globalOffset[1]};


        //update prev values
        lastTheta = theta;
        lastPos = pos;

        pros::delay(10);
    }
}