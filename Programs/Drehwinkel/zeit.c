#include "zeit.h"

static double lastTime = 0;
static double prevTime = 0;


int initTime()
{
    initTimer();
    lastTime = 0;
    TIM2->CNT = 0;
    return 0;
}

double getTime()
{
    return getTimeStamp();
}

void stempTime()
{
    prevTime = lastTime;
    lastTime = getTimeStamp();
}

double getDeltaTime()
{
    if(lastTime < prevTime)
    {
        return (DBL_MAX - prevTime) + lastTime;
    }
    return lastTime - prevTime;
}