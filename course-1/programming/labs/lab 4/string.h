#ifndef STRING_H
#define STRING_H


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

char * inToString(int num)
{
	char * result;
	int backup = num;
	if (num == 0)
	{
		result = calloc(sizeof(char), 2);
		result[0] = '0';
		result[1] = '\0';

		return result;
	}

	int digits = 0;
	while(num != 0)
	{
		digits++;
		num = num / 10; 
	}

	result = calloc(sizeof(char), digits + 1);
	result[digits] = '\0';

	for (int i = digits - 1; i >= 0; i--)
	{
		result[i] = '0' + backup % 10;
		backup = backup / 10; 
	}
	return result;
}

#endif