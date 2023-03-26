#include "main.h"



class Odom {
    private:
        std::atomic<std::vector<double>> pos;
        std::atomic<double> theta;
        
        double lastLeft;
        double lastRight;
        double lastBack;

        double lastTheta;
        double initTheta;
        std::vector<double> lastPos;

        std::vector<double> pos;

    public:
        
        
        void odomTask();
        void reset();
        double getPos();
        void moveToPoint(double x, double y, Drive* drive);
        void turnToPoint(double x, double y, Drive* drive);

};