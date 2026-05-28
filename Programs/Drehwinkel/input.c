#include "input.h"

char input_value;
char reset_button;

int readValues()
{
    input_value = GPIOF->IDR & 3; // read IN0 and IN1:  0011.
    
    return 0;
}

void readButtonInput()
{
    reset_button = GPIOF->IDR & 1 << 6; // read button
}