#include <stdlib.h>
#include <stdio.h>

int const LINE_LENGTH = 80;

FILE * fin;
FILE * fout;


//This function gets the length of a string
int length(char str[])
{
	if (str[0] == 0)
		return 0;
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

//This function counts the number of nonempty lines
int countWords(char **words)
{
	int i = 0;
	while (words[i] != NULL)
		i++;
	if(words[0][0] == '\n')
		return 0;
	return i;
}

void concat(char *into, char *str)
{
	int firstLength = length(into);
	for (int i = 0; i < length(str); i++)
		into[firstLength + i] = str[i];
}

void insert(char *into, int i, char *str)
{
	int delta = length(str);
	for(int j = length(into); j >= i; j--)
		into[j + delta] = into[j];
	
	for(int j = 0; j < length(str); j++)
		into[j + i] = str[j];
}

//This function creates an array of strings containing words from input
void listWords(char line[], char ***words)
{
	int wordIndex = 0, left = 0, right;
	char * word;
	*words = malloc(1);
	while (left < length(line))
	{
		left = getFirstLtr(line, left);
		right = getLastLtr(line, left);
		word = calloc(21, sizeof(int));
		strcopy(word, line, left, right);
		*words = (char**)realloc(*words, (wordIndex + 1) * 21);
		(*words)[wordIndex] = word;
		left = right + 1;
		wordIndex++;
	}
	(*words) = (char**)realloc(*words, (wordIndex) * 21);
	(*words)[wordIndex] = NULL;
}

void sanitize(char *str)
{
	if (str[length(str) - 1] == '\n')
		str[length(str) - 1] = 'n';
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

void buildLine(char *builtLine, char **words, char *prev);
void readLine(char *line, char **words, char *lastLine);

void buildLine(char *builtLine, char **words, char *prev)
{
	builtLine = calloc(LINE_LENGTH + 1, sizeof(char));
	int wordIndex = 0;
	while(wordIndex < countWords(words))
	{
		if (builtLine == NULL)
			builtLine = calloc(LINE_LENGTH + 1, sizeof(char));
		if (length(builtLine) + length(words[wordIndex]) < LINE_LENGTH)
		{
			if (length(builtLine) > 0)
				concat(builtLine, " ");
			concat(builtLine, words[wordIndex]);
			wordIndex++;
		} else
		{
			justify(builtLine);
			printf("%s\n", builtLine);
			free(builtLine);
			builtLine = calloc(LINE_LENGTH + 1, sizeof(char));
		}
	}
}

void readLine(char *builtLine, char **words, char *lastLine)
{

	if (!feof(fin))
	{
		char *line = calloc(1001, sizeof(char));
		fgets(line, 1001, fin);
		sanitize(line);
		listWords(line, &words);
		free(line);
		buildLine(builtLine, words, lastLine);
	}
}

int main ()
{
	fin = fopen("asimov_in.txt", "r");
	fout = fopen("asimov_out.txt", "w");
	
	char *builtLine;
	char *lastLine;
	char **words;

	readLine(builtLine, words, lastLine);
}