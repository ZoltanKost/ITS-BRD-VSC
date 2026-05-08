#include "output.h"


static double elapsedTime = 0;
static double lastTime = 0;

static int angle1 = 0;


int output()
{
    double t = getTime();
    if(t < lastTime)
    {
        elapsedTime = INT_MAX - lastTime + t;
    }else elapsedTime += t - lastTime;
    lastTime = t;
    char s[20] = {0};

    //sprintf(s,"%f\n",elapsedTime);
    //lcdPrintlnS(s);

    if(elapsedTime >= MAX_TIME) return -1;
    if(elapsedTime >= MIN_TIME)
    {
        elapsedTime = 0;
        if(angle1 != angle)
        {
            angle1 = angle;
        }
        sprintf(s,"%f %f\n",angle,angularSpeed);
        lcdPrintlnS(s);
    }

    GPIOD->MODER = GPIOD->MODER | 0x01U << 2*8 | 0x01U << 2*7 | 0x01U << 2*6 | 0x01U << 2*5 
                                | 0x01U << 2*4 | 0x01U << 2*3 | 0x01U << 2*2 | 0x01U << 2*1 | 0x01U; 
    GPIOD->ODR = GPIOD->ODR & ~(impulseNumber & 0xF);
}