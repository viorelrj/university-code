/*
	This program determines the most optimal position to split a string,
	such that the sums of two substrings and the number of their elements coincide as
	much as possible

	Author: Viorel Rinja
*/


#include <stdio.h>
#include <stdlib.h>

int arraySum(int *data, int leftWall, int rightWall)
{
	int sum = 0, i;
	int length = rightWall - leftWall;

	for (i = leftWall; i <= rightWall; i++)
	{
		sum += data[i];
	}

	return sum;
}

int main()
{
	int *data;
	int n, i;
	int minDiff, minIndex;

	scanf("%d", &n);
	data = (int*)calloc(n, sizeof(int));

	for (i = 0; i < n; i++)
	{
		scanf("%d", &data[i]);
	}

	//Setting the initial difference to compare to
	minDiff = abs(arraySum(data, 0, i) - arraySum(data, i + 1, n - 1));
	minIndex = 1;

	int center = (n % 2 == 0)? n / 2 : n / 2 + 1;
	int diff;
	int isOnLeft = 1;

	//We will check all the elements moving from the sides to center
	for (i = 1; i < center; i++)
	{
		//Checking from the left side
		diff = arraySum(data, 0, i) - arraySum(data, i + 1, n - 1);
		if (abs(diff) <= minDiff) 
		{
			minDiff = abs(diff);
			minIndex = i;
			isOnLeft = 1;
		}

		//Checking from the right side
		diff = arraySum(data, n - 1 - i, n - 1) - arraySum(data, 0, n - 2 - i);
		if (abs(diff) <= minDiff) 
		{
			minDiff = abs(diff);
			minIndex = n - 2 - i;
			isOnLeft = 0;
		}  
	}

	printf("%d\n", minIndex + 1);
	printf("%d %d\n", arraySum(data, 0, minIndex), arraySum(data, minIndex + 1, n-1));

	return 0;
}