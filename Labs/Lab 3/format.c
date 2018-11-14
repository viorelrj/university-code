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
	i--;
	for(int j = length(into) + length(str); j >= length(str); j--)
	{
		into[j] = into[j - length(str)];
	}

	// printf("%s\n", into);

	for(int j = i -1; j < length(str); j++)
		into[i + j]= str[j];
}

//This function creates an array of strings containing words from input
void listWords(char line[], char ***words)
{
	// line[length(line) - 1] = '\0';
	int wordIndex = 0, left = 0, right;
	char * word;
	word = calloc(20, sizeof(char));
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

	int lastIndex = countWords(*words);


	(*words) = (char**)realloc(*words, (wordIndex) * 21);
	(*words)[wordIndex] = NULL;
}

void buildLine(char *builtLine, char **words, char *prev);
void readLine(char *line, char **words, char *lastLine);

void buildLine(char *builtLine, char **words, char *prev)
{
	if (length(prev) > 0)
	{
		concat(builtLine, prev);
		prev = calloc(LINE_LENGTH + 1, sizeof(char));

		if (countWords(words) == 0)
			concat(builtLine, "\n");
	}

	int i = 0;
	while (i < countWords(words))
	{
		if (length(builtLine) + length(words[i]) < LINE_LENGTH)
		{
			if (words[i][length(words[i])-1] == '\n')
				words[i][length(words[i])-1] = '\0';
			if (length(builtLine) > 0)
				concat(builtLine, " ");
			concat(builtLine, words[i]);
			i++;
		}
		else
		{
			printf("%s\n", builtLine);
			free(builtLine);
			builtLine = calloc(LINE_LENGTH + 1, sizeof(char));
		}
	}

	if (length(builtLine) > 0)
	{
		prev = calloc(LINE_LENGTH + 1, sizeof(char));
		concat(prev, builtLine);
	}
	readLine(builtLine, words, prev);
}

void readLine(char *builtLine, char **words, char *lastLine)
{
	char *line;

	if (!feof(fin))
	{
		line = calloc(1001, sizeof(char));
		fgets(line, 1001, fin);
		
		listWords(line, &words);

		char * builtLine;
		builtLine = calloc(LINE_LENGTH + 1, sizeof(char));

		buildLine(builtLine, words, lastLine);


		int wordCounter = 0;
	} else 
	if (length(lastLine) > 0)
	{
		line = calloc(1001, sizeof(char));
		listWords(" ", &words);
		char * builtLine;
		builtLine = calloc(LINE_LENGTH + 1, sizeof(char));
		buildLine(builtLine, words, lastLine);
	}
}

int main ()
{
	fin = fopen("asimov_in.txt", "r");
	fout = fopen("asimov_out.txt", "w");
	char *line, *clearLine;
	char **words;
	char *builtLine;


	builtLine = calloc(LINE_LENGTH + 1, sizeof(char));
	clearLine = calloc(LINE_LENGTH + 1, sizeof(char));
	words = malloc(0);


	readLine(builtLine, words, clearLine);
}