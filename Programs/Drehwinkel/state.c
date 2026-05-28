#include "state.h"

#define STATE_00 0
#define STATE_01 1
#define STATE_11 3
#define STATE_10 2

// current Phase
static char currentState = 255;

int impulseNumber = 0;
//double lastPhaseTimestemp = 0;

int direction = 0;
char calculateSpeedFlag = 0;


int updateState()
{
    if(currentState == input_value) return 0; // if phase didnt change, nothing to seek here!
    stempTime(); // update timer
    calculateSpeedFlag = 1;
    direction = 0;
    switch(input_value)
    {
        case STATE_00: // 00
            if(currentState == STATE_11) 
            {
                StateError(3,0);
                return STATE_ERROR;
            }

            if(currentState == STATE_01)// if altes zustand == 1 -> dreht rckwärts
            {
                direction = -1;
            }else if(currentState == STATE_10)
            {
                direction = 1;
            }

            break;
        case STATE_01: // 01
            if(currentState == STATE_10)
            {
                StateError(2,1);
                return STATE_ERROR;
            }

            if(currentState == STATE_11)// if altes zustand == 3 -> dreht rckwärts
            {
                direction = -1;
            }else if(currentState == STATE_00)
            {
                direction = 1;
            }

            break;
        case STATE_11: 
            if(currentState == STATE_00)
            {
                StateError(0,3);
                return STATE_ERROR;
            }

            if(currentState == STATE_10)// if altes zustand == 2 -> dreht rckwärts
            {
                direction = -1;
            }else if(currentState == STATE_01)
            {
                direction = 1;
            } 

            break;
        case STATE_10: 
            if(currentState == STATE_01)
            {
                StateError(1,2);
                return STATE_ERROR;
            }
            
            if(currentState == STATE_00)// if altes zustand == 0 -> dreht rckwärts
            {
                direction = -1;
            }else if(currentState == STATE_11)
            {
                direction = 1;
            }

            break;
    }
    impulseNumber += direction;
    currentState = input_value;
    return 0;
}

void resetState()
{
    initTime();
    currentState = 255;
    calculateSpeedFlag = 0;
    impulseNumber = 0;
    //lastPhaseTimestemp = 0;
    direction = 0;
}