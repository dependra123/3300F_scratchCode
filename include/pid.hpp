#include <iostream>


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

        double compute(double current);
        void setConstants(constants pid_constants);
        constants getConstants();
    
        
};