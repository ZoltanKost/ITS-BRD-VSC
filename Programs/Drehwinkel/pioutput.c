#include "pinoutput.h"

int pinOutput()
{
    // set impulse pins.
    GPIOD->MODER = GPIOD->MODER | GPIOD_WRITE_MASK; 
    GPIOD->BSRR = 0xFF << 16; // reset all pins in D
    GPIOD->BSRR = (impulseNumber & 0xFF); 

    GPIOE->MODER = GPIOE->MODER | GPIOE_WRITE_MASK;

    GPIOE->BSRR = 0xFF << 16; // reset all pins in E

    char set = 0;
    if(error)
    {
        set |= (1 << 5);
    }
    if(direction == 1) set |= 1 << 7;
    else if(direction == -1) set |= 1 << 6; 
    
    
    GPIOE->BSRR = set; 

}