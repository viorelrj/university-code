#include <stdio.h>
#include <stdlib.h>

int main () {

	int n, i, j, max, index;
	int data[10][10];

	scanf("%d", &n);

	//reading the matrix
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &data[i][j]);
		}
	}

	for (i = 0; i < n; i++) {
		//Check every line
		for (j = 1; j < n; j++) {
			//Beginning from the second element,
			//Add up to itself the previous elements.
			data[i][j] += data[i][j - 1];
		}
	}

	max = data[0][n - 1];
	index = 0;

	for (i = 1; i < n; i++) {
		if (data[i][n-1]) {
			max = data[i][n-1];
			index = i;
		}
	}

	printf("%d", index);
 

	return 0;
}