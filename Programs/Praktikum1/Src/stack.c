#include "stack.h"

int stack_init(Stack* stack, unsigned int capacity)
{
    stack->array = malloc(capacity * sizeof(int));
    if(stack->array == 0) 
    {
        printStdout("stack allocation error");
        return -1;
    }
    stack->capacity = capacity;
    if(stack->capacity != 0)printStdout("stack allocation success!");
    return 0;
}

int stack_push(Stack* stack, int element)
{
    if(stack->length >= stack->capacity)
    {
        printStdout("stack push error!");
        return -1;
    }
    printStdout("stack push success!");
    int length = stack->length++;
    stack->array[length] = element;
    return 0;
}

int stack_pop(Stack* stack)
{
    if(stack->length <= 0)
    {
        return -1;
    }
    int length = --stack->length;
    return stack->array[length];
}

int stack_clear(Stack* stack)
{
    stack->length = 0;
}

int stack_readAt(Stack stack, unsigned int index)
{
    int maxIndex = stack.length - 1;
    if(index > maxIndex) return -1;
    printStdout("stack_readAt\n");
    int readIndex = maxIndex - index;
    return stack.array[readIndex];
}

/*
    6   5    4  
    5 ->4 ->  
    4

    6 + 50 + 400
*/
int stack_convertToSingleInt(Stack stack)
{
    int length = stack.length;
    int res = 0;
    int pow = 1;
    while(length-- >= 0)
    {
        res += stack.array[length] * pow;
        pow*=10;
    }
    return res;
}
