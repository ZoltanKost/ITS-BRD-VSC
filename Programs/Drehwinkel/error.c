#include "error.h"

char error = 0;

void StateError(char last, char current)
{
    char s[32]= {0}; 
    sprintf(s, "Wrong state switch: %d -> %d\n", last, current);
    lcdPrintlnS(s);
    error = STATE_ERROR;
}


void TimeError(double time)
{
    char s[64] = {0};
    sprintf(s, "Time error! %f\n", time);
    lcdPrintlnS(s);
    error = STATE_ERROR;
}