#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "string.h"

const int MAX_LENGTH = 200;

void stringToStack (char * string, struct stackNode ** stack)
{
	int i = 0;

	while (string[i] != '\0')
	{
		*stack = stackPush(*stack, string[i]);
		i++;
	}
}

char * binSum(char * num1, char * num2)
{

}

int main()
{
	char * num1 = calloc(sizeof(char), MAX_LENGTH + 1);
	char * num2 = calloc(sizeof(char), MAX_LENGTH + 1);

	gets(num1);
	// gets(num2);

	struct stackNode * stack;
	stackInit(stack);

	// char result = binSum(num1, num2);
	


	stringToStack(num1, &stack);
	stackDisplay(stack);
	printf("%d", stackLength(stack));

	// struct node * head = NULL;

}