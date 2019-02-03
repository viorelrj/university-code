/*
	This program determines the smallest (value) "gap" between any two elements from
	an array 

	Author: Viorel Rinja
*/


#include <stdlib.h>
#include <stdio.h>

int compare(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}

int main () {

	int n, i, *data, index, value;
	scanf("%d", &n);

	data = (int*)calloc(n, sizeof(int));


	for (i = 0; i < n; i++) {
		scanf("%d", &data[i]);
	}

	//Sorting the array, in order to make it easier to check the differenfe
	qsort(data, n, sizeof(int), compare);

	//Setting initial comparation values
	index = 0;
	value = abs(data[1] - data[0]);

	//Checking the absolute value difference
	for (i = 1; i < n - 1; i++) {
		//if the difference is smaller or equal to the current min, set the "king of the hill"
		if (abs(data[i+1] - data[i]) <= value) {
			index = i;
			value = abs(data[i+1] - data[i]);
		}
	}

	//Presenting the result with the first element bigger than the other
	if (data[index] > data[index + 1]){
		printf("%d %d", data[index], data[index + 1]);
	} else {
		printf("%d %d", data[index + 1], data[index]);
	}

	return 0;
}