#include "zeit.h"

static double lastTime = 0;

int initTime()
{
    initTimer();
    lastTime = 0;
    return 0;
}

double getTime()
{
    return getTimeStamp();
}
double getDeltaTime()
{
    double lastTimeTemp = lastTime;
    double temp = getTimeStamp();
    lastTime = temp;
    
    if(temp < lastTimeTemp)
    {
        return (INT_MAX - lastTimeTemp) + temp;
    }
    return temp - lastTimeTemp;
}