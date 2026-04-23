
typedef struct Stack
{
	T_token* array;
	unsigned int length;
	unsigned int capacity;
}


int stack_init(unsigned int lenght);

int stack_push(Stack stack, T_token element);

int stack_pop(Stack stack, T_token* resultCopy);

int stack_clear(Stack stack);

int stack_readAt(Stack stack, unsigned int index, T_token* resultCopy);
