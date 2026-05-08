#include "update.h"

// winkelgeschwindigkeit = 360 / 1200 -> winkel pro 1 phasenuebergang
// 0.3 / deltatime = winkelgeschwindigkeit
double angularSpeed = 0;

// winkel = impulseNumber * 0.3f;
// 1200 / 360 = umdrehung / winkel; => winkel = 360 * umdrehung / 1200
double angle = 0;

int updateValues()
{
    if(!calculateSpeedFlag) return 0;
    int number = impulseNumber;
    calculateSpeedFlag = 0;
    // if time exceeded
    //if()
    angularSpeed = 0.3 * 90000000 / lastPhaseTimestemp; 
    angle = impulseNumber * 0.3f;
}

int initUpdate()
{
    angularSpeed = 0;
    angle = 0;
}