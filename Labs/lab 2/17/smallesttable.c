#include <stdio.h>
#include <stdlib.h>

int getMinIndex(int data[100][100], int k, int n) {
	int i;
	int minIndex = 0;
	int min = data[0][k];

	for (i = 0; i < n; i++) {
		if (data[i][k] < min) {
			min = data[i][k];
			minIndex = i;
		}
	}

	printf("minIndex: %d", minIndex);
	return minIndex;
}

int getMaxIndex(int data[100][100], int k, int n) {
	int i;
	int maxIndex = 0;
	int max = data[k][0];

	for (i = 0; i < n; i++) {
		if (data[k][i] > max) {
			max = data[k][i];
			maxIndex = i;
		}
	}

	return maxIndex;
}


int main () {

	int data[100][100], rows[100], cols[100];
	int i, k, n;

	scanf("%d", &n);

	//reading the array

	for (i = 0; i < n; i++) {
		for (k = 0; k < n; k++) {
			scanf("%d", &data[i][k]);
		}
	}

	for (i = 0; i < n; i++) {
		for (k = 0; k < n; k++) {
			printf("%d ", data[i][k]);
		}
		printf("\n");
	}

	for (i = 0; i < n; i++) {
		cols[i] = getMinIndex(data, i, n);
		rows[i] = getMaxIndex(data, i, n);
	}

	printf("Next is debugging: \n");
	for (i = 0; i < n; i++){
		printf("%d ", cols[i]);
	}
	printf("\n");

	for (i = 0; i < n; i++){
		printf("%d ", rows[i]);
	}

	return 0;
}