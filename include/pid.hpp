#include <iostream>
#include<vector>

class PID{
    public:
        struct constants{
            double kP;
            double kI;
            double kD;
            double start_i;
            
        };
        
        constants pidConstants;

        double derivative;
        double proportional;
        double integral;

        double error;
        double lastError;
        double target;
        double output;

         struct slew_ {
            int sign = 0;
            double error = 0;
            double x_intercept = 0;
            double y_intercept = 0;
            double slope = 0;
            double output = 0;
            bool enabled = false;
            double max_speed = 0;
            double tickPerInch = 0;
        };



        double compute(double current);
        void setConstants(constants pid_constants);
        constants getConstants();

        //slew stuff
        std::vector<double> slewMinPower;
        std::vector<double> slewDistance;
    
        
        slew_ slew;


        void setSlewMinPower(std::vector<double> minPower);
        void setSlewDistance(std::vector<double> distance);
        void slewInit( bool slewOn, int maxSpeed, double target, double current, double start, bool isBackwards, int ticks_per_inch);

        double slewCalc( double current);


        
};