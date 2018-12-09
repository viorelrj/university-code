/*
	This program takes sequences of strings (up to 1000 chars) and
	distributes the word in a non-destructive way on lines of 
	LINE_LENGTH (default 80) characters, using justify with priority
	to left.

	Author: Viorel Rinja
*/

#include <stdlib.h>
#include <stdio.h>

int const LINE_LENGTH = 80;

FILE * fin;
FILE * fout;


//This function gets the length of a string
int length(char str[])
{
	//If the string is null
	if (str[0] == 0)
		return 0;
	//Count letters until the null terminator
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

//This function cuts a string at a certain index
void cut(char *str, int index, int num)
{
	for (int i = index; i <= length(str) - num; i++)
		str[i] = str[i+num];
}

//This function inserts a string into another string at a certain index
void insert(char *into, int i, char *str)
{
	//Move characters aside 
	int delta = length(str);
	for(int j = length(into); j >= i; j--)
		into[j + delta] = into[j];

	//Insert the string into the free space creating after moving
	for(int j = 0; j < length(str); j++)
		into[j + i] = str[j];
}

//This function eliminates the new line elements from string
void sanitize(char *str)
{
	//Getting rid of "new line terminations"
	if (str[length(str) - 1] == '\n')
		str[length(str) - 1] = '\0';

	for (int i = 0; i < length(str); i++)
		if (str[i] == '\n' || str[i] == '\r')
			cut(str, i, 1);

	//Get rid of multiple spaces, if there are any
	int left = 0;
	int right = 0;

	while (left < length(str))
	{
		//Find a space
		right = getFirstLtr(str, left);
		//If it spans for more than one char
		if (right - left > 1)
			//Remove all but one space characters from the sequence
			cut(str, left, right - left - 1);

		//Find next space
		left = getLastLtr(str, right);
	}
}


//This implements justify functionality by adding spaces
void justify(char *str)
{
	int spaceIndex = 0;

	int i = length(str) - 1;
	while(str[i] == ' ')
		cut(str, i--, 1);
	
	//As long as the line does not span for the full width possible
	while(length(str) < LINE_LENGTH)
	{
		//Add a space near every space, LTR, ciclically
		if(spaceIndex == length(str) - 1)
			spaceIndex = 0;
		spaceIndex = getFirstLtr(str, spaceIndex);
		spaceIndex = getLastLtr(str, spaceIndex);
		insert(str, spaceIndex, " ");
	}
}

/*
	These two functions, in a recursive way, read line from the file,
	divide, sanitize spaces and new lines, and output them to the fout. (file out)

	in this context:
		Appendix - the leftover from the last line
*/
void buildLine(char *line, char *prev);
void readLine(char *line, char *prev);

void buildLine(char *line, char *prev)
{
	//If there is nothing else to read, display, the appendix
	if (feof(fin)){
		fprintf(fout, "%s", prev);
		return;
	}

	//Sanitize the string 
	sanitize(line);

	/*
		After sanitizing, the length of a blank line with "\r\n" has length 0
		Thus, display the appendix with'\n', and proceed to next input line
	*/
	if (length(line) == 0)
	{
		fprintf(fout, "%s\n", prev);
		free(prev);
		prev = calloc(LINE_LENGTH + 1, sizeof(char));
		return readLine(line, prev);
	}

	//If it is not an empty line, put the appendix to the beginning of the line
	insert(line, 0, prev);
	char *builtLine;

	//As long as the inputLine is not null (we will be cutting from it)
	while (length(line) > 0)
	{
		//Find the wall (the index of the last letter of last word that completely fits)
		int wall; 
		if (length(line) > LINE_LENGTH)
		{
			//From the max length, move to left, till the first space
			wall = LINE_LENGTH;
			while(line[wall] != ' ')
				wall--;
		}
		else
			//If the line is smaller than the limit, just put the wall at its end
			wall = length(line) - 1;

		//Copy the segment that fits into a builtLine (the output line)
		builtLine = calloc(LINE_LENGTH, sizeof(char));
		strcopy(builtLine, line, 0, wall + 1);

		//If it is not the last line in the block, justify it and display
		if (length(line) > LINE_LENGTH)
		{
			justify(builtLine);
			fprintf(fout, "%s\n", builtLine);			
		} 
		else 
		{
			/*
				If is the last line in block, add a space to it (so it could pe inserted into 
				a string that will start with a letter
			*/
			prev = calloc(LINE_LENGTH + 1, sizeof(char));
			concat(prev, builtLine);
			concat(prev, " ");
		}

		//Manage the memory not to leak
		free(builtLine);
		cut(line, 0, wall + 1);	
	}

	//If did not reach to the end of the file, read another line
	if (!feof(fin))
		readLine(line, prev);
}

void readLine(char *line, char *prev)
{
	//If not the end of the file, get the line
	if (!feof(fin))
	{
		line = calloc(1001 + LINE_LENGTH + 1, sizeof(char));
		fgets(line, 1001, fin);
		buildLine(line, prev);
	} 
	//If it is the end of the file, just output the appendix
	else {
		buildLine(line, prev);
	}
}

int main ()
{
	fin = fopen("asimov_tests/asimov_05i.txt", "r");
	fout = fopen("asimov_out.txt", "w");

	char *line, *prev;
	prev = calloc(LINE_LENGTH + 1, sizeof(char));

	readLine(line, prev);

	fclose(fin);
	fclose(fout);
}