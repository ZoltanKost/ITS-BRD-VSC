#include "input.h"
#include "zeit.h"
#include "error.h"
#include "output.h"


extern char currentState;

extern int direction;
extern char calculateSpeedFlag;
//extern double lastPhaseTimestemp;
extern int impulseNumber;

extern char phasenWechsel;
extern char mussPhasenWechselLesen;


int updateState();
void resetState();