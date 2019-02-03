/*
	This program concatinates two given strings.

	Author: Viorel Rinja
*/

#include <stdio.h>
#include <stdlib.h>

const int MAX_READ_LENGTH = 256;


//Function which gets the length of a string
int length(char *arr) 
{
	int counter = 0;


	while(arr[counter] != '\0')
	{
		counter++;
	}

	return counter;
}


int main () 
{

	char *input, *concat;
	int firstSize, finSize;

	input = (char*)calloc(MAX_READ_LENGTH, sizeof(char));

	//reading from user input
	gets(input);

	//Getting the length of the initial string and allocating memory
	//Not forgetting about the null terminator
	firstSize = length(input);
	concat = (char*)calloc(firstSize + 1, sizeof(char));

	//Storing the data into the array to be concatinated into
	for (int i = 0; i <= firstSize; i++)
	{
		concat[i] = input[i];
	}

	//Getting ready to receive the next input to be concatinated
	free(input);

	input = (char*)calloc(MAX_READ_LENGTH, sizeof(char));

	//rading the second string
	gets(input);

	//Determining the size of the concatenated string and allocating memory
	//Not forgetting about the null terminator
	finSize = firstSize + length(input);
	concat = (char*)realloc(concat, finSize + 1);

	//Concatenating the strings
	for (int i = 0; i < finSize - firstSize; i++)
	{
		concat[i + firstSize] = input [i];
	}

	printf("%s\n", concat);

	return 0;
}