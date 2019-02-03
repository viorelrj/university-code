/*
	This program implements the functionality of numbering system conversion
	using operations on strings

	Author: Viorel Rinja
*/

#include <stdio.h>
#include <stdlib.h>

//This function gets the length of a string
int length(char str[])
{
	//If null string
	if (str[0] == 0)
		return 0;
	//Counting each element, till the null terminator
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

//This function inserts a char into a string in a specific position
void insertChar(char *into, int i, char character)
{
	for(int j = length(into); j >= i; j--)
		into[j + 1] = into[j];
	into[i] = character;
}


//This function converts integers to char, with possibility of 
//using letters as digits (fore numbering systems with more than 10 digits)
char intToChar(int num)
{
	if (num < 10)
		return num + '0';
	else
		return (num - 10) + 'A';
}

//Convert an integer to a base between 0 and 16
char * intDecToX(int num, int base)
{
	//Create the output variable, using dynamic memory
	int digits = 1;
	char * result;
	result = malloc(sizeof(char) * digits);
	result[0] = '\n';

	/*
		As long as the number is not equal to 0, put reminder of the division
		between number and base in the beginning of the result string.
		After that, divide the number by base and proceed to the next itteration of while
	*/
	while (num != 0)
	{
		result = realloc(result, sizeof(char) * ++digits);

		insertChar(result, 0, intToChar(num % base));
		num = num / base;
	}

	return result;
}

int main ()
{
	char * number;
	number = intDecToX(625341, 16);
	
	printf("%s", number);
	return 0;
}