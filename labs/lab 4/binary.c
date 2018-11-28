#include <stdio.h>
#include <stdlib.h>
#include "string.h"

const int MAX_LENGTH = 200;

int charToInt(char digit)
{
	return digit - '0';
}

char * inToChar(int number)
{
	if (number == 1)
		return "1";
	if (number == 0)
		return "0";
}

char * binSum(char * num1, char * num2)
{
	//Make the length equal
	while (length(num1) != length(num2))
	{
		if (length(num1) > length(num2))
			insert(num2, 0, "0");

		if (length(num2) > length(num1))
			insert(num2, 0, "0");
	}

	char * result = calloc(sizeof(char), length(num1) + length(num2) + 1);
	result[0] = '\0';

	int digit1, digit2, memDigit = 0;

	for(int i = length(num1) - 1; i >= 0; i--)
	{
		digit1 = charToInt(num1[i]);
		digit2 = charToInt(num2[i]);

		insert(result, 0, inToChar((digit1 + digit2 + memDigit) % 2));
		memDigit = (digit1 + digit2 + memDigit) / 2;
	}
	if (memDigit != 0) insert(result, 0, "1");
	
	return result;
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