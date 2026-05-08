#include "state.h"

#define STATE_00 0
#define STATE_01 1
#define STATE_11 3
#define STATE_10 2

// current Phase
static char currentState;

int impulseNumber = 0;
double lastPhaseTimestemp = 0;

int direction = 0;
char calculateSpeedFlag = 0;


int updateState()
{
    if(currentState == input_value) return 0; // if phase didnt change, nothing to seek here!
    lastPhaseTimestemp = getDeltaTime(); // update timer
    calculateSpeedFlag = 1;
    switch(input_value)
    {
        case STATE_00: // 00
            if(currentState == STATE_11) 
            {
                // TODO: ERROR!
            }
            direction = currentState == STATE_01? -1 : 1; // if altes zustand == 1 -> dreht rckwärts
            currentState = input_value;
            break;
        case STATE_01: // 01
            if(currentState == STATE_10)
            {
                //TODO: ERROR!
            }
            direction = currentState == STATE_11? -1 : 1; // if altes zustand == 3 -> dreht rckwärts
            currentState = input_value;
            break;
        case STATE_11: // 10
            if(currentState == STATE_00)
            {
                //TODO: ERROR!
            }
            direction = currentState == STATE_10? -1 : 1; // if altes zustand == 2 -> dreht rckwärts
            currentState = input_value;
            break;
        case STATE_10: // 11
            if(currentState == STATE_01)
            {
                //TODO: ERROR!
            }
            direction = currentState == STATE_00? -1 : 1; // if altes zustand == 0 -> dreht rckwärts
            currentState = input_value;
            break;
    }
    impulseNumber += direction;
}

int resetState()
{
    initTime();
    currentState = 0;
    calculateSpeedFlag = 0;
    impulseNumber = 0;
    lastPhaseTimestemp = 0;
    direction = 0;
}