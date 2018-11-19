#include <stdlib.h>
#include <stdio.h>

int const LINE_LENGTH = 80;

FILE * fin;
FILE * fout;

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

//This function copies a part of a string into another stirng
void strcopy(char * into, char from[], int left, int right)
{
	for (int i = 0; left + i < right; i++)
		into[i] = from[left + i];
}

//This function gets the first occurance of a not space character
int getFirstLtr(char str[], int i)
{
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	return i;
}

//This function gets the last occurance of a letter before space
int getLastLtr(char str[], int i)
{
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return i;
}

//This function concatenates two strings
void concat(char *into, char *str)
{
	int firstLength = length(into);
	for (int i = 0; i < length(str); i++)
		into[firstLength + i] = str[i];
}

//This function shortens a string by eliminating a sequence of its characters
void cut(char *str, int index, int num)
{
	for (int i = index; i < length(str) - num; i++)
	{
		str[i] = str[i+num];
	}
}

//This function inserts a string into another in a specific position
void insert(char *into, int i, char *str)
{
	int delta = length(str);
	for(int j = length(into); j >= i; j--)
		into[j + delta] = into[j];
	
	for(int j = 0; j < length(str); j++)
		into[j + i] = str[j];
}

void sanitize(char *str)
{
	if (str[length(str) - 1] == '\n')
		str[length(str) - 1] = '\0';
}

void unixLine(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\r')
			cut(str, i, 1);
		i++;
	}
}

void justify(char *str)
{
	int spaceIndex = 0;
	
	while(length(str) < LINE_LENGTH)
	{
		if(spaceIndex == length(str) - 1)
			spaceIndex = 0;
		spaceIndex = getFirstLtr(str, spaceIndex);
		spaceIndex = getLastLtr(str, spaceIndex);
		insert(str, spaceIndex, " ");
	}
}
