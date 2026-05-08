#include "scanner.h"
#include "stack.h"
#include "display.h"
#include <assert.h>

int initReader();

int addition(int n1, int n2);

int multiplication(int n1, int n2);

int division(int n1, int n2);

int substraction(int n1, int n2);

int print(int number);

int print_all(Stack s);

int swap(Stack* s);

int duplicate(Stack* s);

int clear(Stack* s);

int enter(Stack* s);

int readToken(Stack* s);