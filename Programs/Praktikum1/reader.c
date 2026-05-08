#include "reader.h"

#define MAX_TOKEN_LENGTH 16

int readToken(Stack* s)
{
	T_token token = nextToken();
	if(token.tok != NUMBER)
	{
		switch(token.tok)
		{
			case PLUS:
				stack_push(s,addition(stack_pop(s),stack_pop(s)));
				break;
			case MINUS: 
				stack_push(s,substraction(stack_pop(s),stack_pop(s)));	
				break;
			case DIV: 
				stack_push(s,division(stack_pop(s),stack_pop(s)));	
				break;
			case MULT:
				stack_push(s,multiplication(stack_pop(s),stack_pop(s)));
				break;
			case PRT     :
				print(stack_readAt(*s, 0));
				break;
			case SWAP    :
				swap(s);
				break;
			case PRT_ALL :
				print_all(*s);
				break;
			case CLEAR   :
				clear(s);
				break;
			case DOUBLE  :
				duplicate(s);
				break;
		}
	}
	else if(stack_push(s,token.val) != -1)
	{
		return 0;
	}else
	return -1;
}


int addition(int n1, int n2)
{
    return n1 + n2;
}

int multiplication(int n1, int n2)
{
    return n1 * n2;
}

int division(int n1, int n2)
{
    return n1 / n2;
}

int substraction(int n1, int n2)
{
    return n1 - n2;
}

int print(int number)
{
    int temp = number;
    int l = 0;
    while(temp > 0)
    {
        temp = temp / 10;
        l++;
    }
    char string[10] = {0};
    
    for(int i = 0; i < l; i++)
    {
        string[l-i-1] = number % 10 + 0x30;
        number = number / 10;
    }
    printStdout(string);
}

int print_all(Stack s)
{
    return -1;
}

int swap(Stack* s)
{
    return -1;
}

int duplicate(Stack* s)
{
    return -1;
}

int clear(Stack* s)
{
    return -1;
}
 