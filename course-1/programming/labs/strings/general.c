/*
	This file contains custom functions of string (arrays of chars really)
	processing

	Author: Viorel Rinja
*/



#include <stdlib.h>
#include <stdio.h>


/*-------------- Constants  --------------*/

int const MAX_LENGTH = 256;

/*----------  End of Constants  ----------*/





/*================================
=            Utilites            =
================================*/

int strLen(char *string)
{
	int counter = 0;

	while(string[counter] != '\0')
	{
		counter++;
	}

	return counter;
}


/*=====  End of Utilites  ======*/





/*========================================
=            String Utilities            =
========================================*/


/*----------  Concatenation  ----------*/


char *concat(char str1[], char str2[])
{
	char *result;

	int lefLength = strLen(str1);
	int length = lefLength + strLen(str2);

	//Calculating the length of the concatenated string
	result = calloc(length + 1, sizeof(char));

	//Putting the first string
	for(int i = 0; i < strLen(str1); i++)
	{
		result[i] = str1[i];
	}

	//Putting the second string, continuing from the place first
	//string ended
	for(int i = 0; i < strLen(str2); i++)
	{
		result[lefLength + i] = str2[i];
	}

	//Setting the null terminator
	result[length] = '\0';

	return result;
}


/*----------  Seek  ----------*/

int seek(char str1[], char str2[])
{
	/*
		We will consider the string to seek in as haystack
		And the segment of string to be found as needle
	*/

	//If the needle is bigger than the haystack, it is 
	//useless to sick for it.
	if(strLen(str2) > strLen(str1))
		return -1;

	//Checking every position of the haystack
	for(int i = 0; i <= strLen(str1) - strLen(str2); i++)
	{
		//Checking every position of the needle
		int j = 0;
		//If the elements coincide, check the next elements
		while (str1[i + j] == str2[j])
		{
			//If the elements are equal till the last element
			//The needle occurance has been found, so return the index
			if (j == strLen(str2))
				return i;
			else
				//if did not get to the end, proceed to the next itteration
				j++;
		}
	}

	return -1;
}


/*=====  End of String Utilities  ======*/





int main()
{

	
	return 0;
}