#include "stm32f4xx_hal.h"
#include "state.h"
#include "error.h"

#define GPIOD_WRITE_MASK (0x01U<<2*8|0x01U<<2*7|0x01U<<2*6\ 
    |0x01U << 2*5|0x01U<<2*4|0x01U<<2*3|0x01U<<2*2| 0x01U << 2*1 | 0x01U)
#define GPIOE_WRITE_MASK 0x01U << 5 * 2 | 0x01U << 6 * 2 | 0x01U << 7 * 2
// 0x 01 01 01 01 01 01 01 01

int pinOutput();