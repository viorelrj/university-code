/*

	This program determines the number of occurance of the longest "Gates" in topologic
	surface

	Author: Viorel Rinja

*/


#include <stdlib.h>
#include <stdio.h>

int main() 
{
	FILE *fin;
	FILE *fout;
	
	int map[200][200];
	int i, j, k, n;
	int trackLength, maxLength = 0, count = 0;

	fin = fopen("DEF.IN", "r");

	fscanf(fin, "%d", &n);

	for(i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			fscanf(fin, "%d", &map[i][j]);
		}
	}

	fclose(fin);

	fout = fopen("DEF.OUT", "w");


	//Checking every line, beginning from the second
	for (i = 1; i < n - 1; i++)
	{
		//Starting to count the paths
		j = 0;
		trackLength = 0;

		while (j < n)
		{
			//If satisfies the condition of "gate"
			if (map[i-1][j] > map[i][j] && map[i+1][j] > map[i][j])
			{
				//Increment the size of the current track length
				trackLength++;

				//Managing the maximal values
				if (trackLength > maxLength)
				{
					//if bigger, reset counter and set new Biggest
					maxLength = trackLength;
					count = 1;
				} else if (trackLength == maxLength)
				{
					//If equal, increment the counter
					count++;
				}
			} else 
			{
				trackLength = 0;
			}

			j++;
		}
	}

	fprintf(fout, "%d", maxLength);

	fclose(fout);

	return 0;
}