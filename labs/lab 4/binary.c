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

char * binSum(char * num1, char * num2);

char * negatify (char * number)
{
	insert(number, 0, "0");
	//Make the inverse representation of the code
	for(int i = 0; i < length(number); i++)
		if (number[i] == '0')
			number[i] = '1';
		else
			number[i] = '0';

	char * one = calloc(sizeof(char), MAX_LENGTH);
	one[0] = '0';
	one[1] = '1';
	one[2] = '\0';

	number = binSum(number, one);
	cut(number, 0, 1);

	return number;
}

char * parse(char * number)
{
	if (number[0] == '-')
	{
		cut(number, 0, 1);
		number = negatify(number);
	}

	return number;
}

char * binSum(char * num1, char * num2)
{
	//Make the length equal
	while (length(num1) != length(num2))
	{
		if (length(num1) > length(num2))
			insert(num2, 1, "0");
		else
			insert(num1, 1, "0");
	}

	char * result = calloc(sizeof(char), length(num1) + length(num2) + 1);
	result[0] = '\0';

	int digit1, digit2, memDigit = 0;

	for(int i = length(num1) - 1; i > 0; i--)
	{
		digit1 = charToInt(num1[i]);
		digit2 = charToInt(num2[i]);

		insert(result, 0, inToChar((digit1 + digit2 + memDigit) % 2));
		memDigit = (digit1 + digit2 + memDigit) / 2;
	}
	(memDigit != 0)? insert(result, 0, "1") : insert(result, 0, "0");
	
	return result;
}

char * binDif(char * num1, char * num2)
{
	while (length(num1) != length(num2))
	{
		if (length(num1) > length(num2))
			insert(num2, 1, "0");
		else
			insert(num1, 1, "0");
	}

	num2 = negatify(num2);

	char * result = calloc(sizeof(char), length(num1) + length(num2) + 1);
	result[0] = '\0';

	int digit1, digit2, memDigit = 0;

	for(int i = length(num1) - 1; i > 0; i--)
	{
		digit1 = charToInt(num1[i]);
		digit2 = charToInt(num2[i]);

		insert(result, 0, inToChar((digit1 + digit2 + memDigit) % 2));
		memDigit = (digit1 + digit2 + memDigit) / 2;
	}
	(memDigit != 0)? insert(result, 0, "0") : insert(result, 0, "1");
	
	return result;
}

char * binProd(char * num1, char * num2)
{
	char * result = calloc(sizeof(char), length(num1) + length(num2));
	result[0] = '0';
	result[1] = '0';
	result[2] = '\0';
	for(int i = length(num1) - 1; i > 0; i--)
	{
		if(num1[i] == '1')
			result = binSum(result, num2);
		insert(num2, length(num2), "0");
		printf("%s\n", result);
	}

	if (num1[0] == num2[1])
		result[0] = '0';
	else result[0] = '1';

	return result;
}

int main()
{
	char * num1 = calloc(sizeof(char), MAX_LENGTH + 1);
	char * num2 = calloc(sizeof(char), MAX_LENGTH + 1);

	gets(num1);
	gets(num2);

	num1 = parse(num1);
	num2 = parse(num2);
	printf("%s", binProd(num1, num2));

	return 0;
}