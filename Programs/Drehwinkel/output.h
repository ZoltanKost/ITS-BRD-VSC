#include "update.h"
#include "state.h"
#include "lcd.h"
#include <stdio.h>
#include "error.h"
#include <string.h>

#define MIN_TIME 22500000
#define MAX_TIME 45000000

int output();
void resetOutputTime();
void outputString(char* angle, char* speed);