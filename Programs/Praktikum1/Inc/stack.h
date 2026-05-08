#include "token.h"
#include "display.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Stack
{
	int* array;
	unsigned int length;
	unsigned int capacity;
	//unsigned int element_size;
} Stack;

int stack_init(Stack* stack, unsigned int lenght);

int stack_push(Stack* stack, int element);

int stack_pop(Stack* stack);

int stack_clear(Stack* stack);

// Reads LAST ADDED element. Read at 0 returns element that would be deleted when stack_pop();
int stack_readAt(Stack stack, unsigned int index);

int stack_convertToSingleInt(Stack stack);
