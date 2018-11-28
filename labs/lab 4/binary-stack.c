#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "string.h"

const int MAX_LENGTH = 200;

int charToInt(char * digit)
{
	return digit[0] - '0';
}

char inToChar(int number)
{
	return number + '0';
}

void stringToStack (char * string, struct stackNode ** stack)
{
	int i = 0;

	while (string[i] != '\0')
	{
		*stack = stackPush(*stack, string[i]);
		i++;
	}
}

void binSum(char * num1, char * num2)
{
	struct stackNode * stack1;
	stackInit(stack1);
	stringToStack(num1, &stack1);

	struct stackNode * stack2;
	stackInit(stack2);
	stringToStack(num2, &stack2);

	struct stackNode * result;
	stackInit(result);

	char * digit1, * digit2;
	int integ1, integ2, memDigit = 0;

	while(stack1 != NULL && stack2 != NULL)
	{
		stackPop(stack1, digit1);
		stackPop(stack2, digit2);

	// 	// integ1 = charToInt(digit1);
	// 	// integ2 = charToInt(digit2);

	// 	// stackPush(result, inToChar((integ1 + integ2 + memDigit) % 2));
	// 	// memDigit = (integ1 + integ2) / 2;
	}

	// stackDisplay(result);
}

int main()
{
	char * num1 = calloc(sizeof(char), MAX_LENGTH + 1);
	char * num2 = calloc(sizeof(char), MAX_LENGTH + 1);

	gets(num1);
	gets(num2);

	binSum(num1, num2);

	return 0;
}