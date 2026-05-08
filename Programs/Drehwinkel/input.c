#include "input.h"

char input_value;

int readValues()
{
    input_value = GPIOF->IDR & 3; // read IN0 and IN1:  0011.
    return 0;
}