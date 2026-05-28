#include "lcd.h"
#include <stdio.h>

#define STATE_ERROR -1

extern char error;

void StateError( char last, char current);
void TimeError(double time);