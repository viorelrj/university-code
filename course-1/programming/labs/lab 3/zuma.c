/*
	This program is a proto-zuma clone that has the functionality
	to detect if a "shot" will "explode", and make it explode recursively.

	Author: Viorel Rînja
*/


#include <stdlib.h>
#include <stdio.h>

FILE *fl;

int length(char *row)
{
	int i = 0;
	while (row[i] != '\0')
		i++;
	return i;
}

/*
	The evaluate and explode functions are mutually recursive,
	thus we have to declare them ahead (forward declaration.
*/
int evaluate(int i, char *row);

//This function produces a recursife explosion
int explode(int i, char *row)
{
	//Initializing the left and right bound of explosion
	int left, right;
	left = i;
	right = i;

	//Getting the left and right bounds of the explosion
	while(row[left] == row[left - 1])
		left--;
	while(row[right] == row[right + 1])
		right++;

	//Getting the difference of explosion, to cut the string
	int delta = right - left + 1;

	//Cutting the string
	for (int i = left; i <= length(row) - delta; i++)
		row[i] = row[i+delta];

	evaluate(left - 1, row);
	evaluate(left, row);
}

//This function evaluate wether an explosion will happen
int evaluate(int i, char *row)
{
	//Handling exception of out of range index
	if (i < 0 || i >= length(row))
		return 0;

	//if middle, left and right elements are equal, explode
	if (row[i-1] == row[i] && row[i] == row[i+1])
	{
		explode(i, row);
		return 1;
	}

	return 0;
}


int main()
{
	//Openning the input file
	fl = fopen("zuma.in", "r");

	//Reading the shooting addres
	int addres;
	fscanf(fl, "%d", &addres);

	//Converting to counting from 0;
	addres--;

	//Get the row with chars
	char *row;
	row = (char*)calloc(201, sizeof(char));
	fscanf(fl, "%s", row);

	//Closing the input file
	fclose(fl);

	//Evaluate the explosion
	evaluate(addres, row);

	//Opening the output file, putting the output and saving
	fl = fopen("zuma.out", "w");
	fprintf(fl, "%s", row);
	fclose(fl);

	return 0;
}