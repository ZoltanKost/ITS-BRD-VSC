#include "output.h"


static double elapsedTime = 0;
static double lastOutputTime = 0;

static char angleString[5];
static char speedString[5];

static int angle1 = 0;

int output()
{
    double t = getTime();
    if(t < lastOutputTime)
    {
        elapsedTime = t;
    }else elapsedTime += t - lastOutputTime;
    lastOutputTime = t;

    if(elapsedTime >= MAX_TIME) 
    {
        //elapsedTime = 0;
        TimeError(elapsedTime);
        return -1;
    }
    if(elapsedTime >= MIN_TIME)
    {
        elapsedTime = 0;
        if(angle1 != (int)angle)
        {
            angle1 = angle;
            char s1[7] = {0};
            char s2[5] = {0};   
            sprintf(s1,"%.1f",angle);
            sprintf(s2,"%.1f",angularSpeed);
            outputString(s1,s2);
            //lcdPrintS(s);
        }
    }
    return 0;
}

void resetOutputTime()
{
    lastOutputTime = 0;
    elapsedTime = 0;
    //lcdPrintlnS("Time resetted");
}
void outputString(char* angle, char* speed)
{
    for(int i = 0; i < 5; i++)
    {
        if(angle[i] == 0) break;
        if(angle[i] != angleString[i])
        {
            lcdGotoXY(i,5);
            lcdPrintC(angle[i]);
            angleString[i] = angle[i];
        }
    }

    for(int i = 0; i < 5; i++)
    {
        if(speed[i] == 0) break;
        if(speed[i] != speedString[i])
        {
            lcdGotoXY(i,7);
            lcdPrintC(speed[i]);
            speedString[i] = speed[i];
        }
    }
    strcpy(angle,angleString);
    strcpy(speed,speedString);
}