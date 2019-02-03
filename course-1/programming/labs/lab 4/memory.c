#include <stdlib.h>
#include <stdio.h>
#include "string.h"

const int SIZE = 16;

char * toBin(int number)
{
	char * result = calloc(sizeof(char), SIZE + 1);
	result[SIZE] = '\0';

	for(int i = 0; i < SIZE; i++)
		result[SIZE - i -1] = ((number & 1<<i) == 1<<i) + '0';

	return result;
}

char * toBinDir(int number)
{
	char * result = calloc(sizeof(char), SIZE + 1);
	result[SIZE] = '\0';
	if(number < 0)
	{
		result[0] = '1';
		number = -number;
	}
	else
		result[0] = '0';
	for(int i = 0; i < SIZE - 1; i++)
		result[SIZE - i -1] = ((number & 1<<i) == 1<<i) + '0';

	return result;
}


char * toBinInv(int number)
{
	char * result = calloc(sizeof(char), SIZE + 1);
	result[SIZE] = '\0';

	if (number > 0)
		result[0] = '0';
	else
	{
		result[0] = '1';
		number = ~(- number);
	}

	for(int i = 0; i < SIZE; i++)
		result[SIZE - i -1] = ((number & 1<<i) == 1<<i) + '0';

	return result;
}

char * toBinComp(int number){
	char * result = calloc(sizeof(char), SIZE + 1);
	result[SIZE] = '\0';

	if (number > 0)
		result[0] = '0';
	else
		result[0] = '1';
		
	for(int i = 0; i < SIZE; i++)
		result[SIZE - i -1] = ((number & 1<<i) == 1<<i) + '0';

	return result;
}

char * normalize(char * input, char * base)
{
	int zero = (input[0] == '-')? 1: 0;
	//Find point
	int pointIs = zero;
	while(input[pointIs] != '.' && input[pointIs] != '\0')
		pointIs++;

	//find first non-zero digit
	int pointShouldBe = zero;
	while((input[pointShouldBe] == '0' || input[pointShouldBe] =='.') && input[pointShouldBe] != '\0')
		pointShouldBe++;

	pointShouldBe = (pointShouldBe == zero)? zero + 1: pointShouldBe;

	cut(input, pointIs, 1);
	insert(input, pointShouldBe, ".");

	//Count zeros before point
	int countZero = zero;
	while (input[countZero] == '0' && input[countZero] != '.' && input[countZero] != '\0')
		countZero++;
	if (input[countZero + 1] == '.')
		countZero++;
	countZero -= zero;

	//Sanitize of multiple zero's before the point
	if (countZero > 1)
		cut(input, zero, countZero - 1);

	//Sanitize from spare zeros from right
	countZero = length(input) -1;
	while (input[countZero] == '0' && input[countZero] != '.' && input[countZero] != '\0')
		countZero--;
	cut(input, countZero + 1, length(input) - 1 - countZero);

	int exp = pointIs - pointShouldBe;
	char * expString = inToString(abs(exp));

	concat(input, "*");
	concat(input, base);
	concat(input, "^");
	if (exp < 0) concat(input, "(-");
	concat(input, expString);
	if (exp < 0) concat(input, ")");
	return input;
}

int main ()
{
	char * test = calloc(sizeof(char), 50);
	gets(test);
	test = normalize(test, "10");
	printf("%s", test);
	return 0;
}