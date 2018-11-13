#include <stdio.h>
#include <stdlib.h>

int secondDiag(int data[100][100], int n) {

	int i, sum;
	sum = 0;

	for (i = 0; i < n; i++) {
		sum += data[i][n - 1 - i];
	}

	return sum;
}

int upperDiag(int data[100][100], int n) {

	int i, sum;
	sum = 0;

	for (i = 1; i < n; i++) {
		sum += data[i-1][i];
	}

	return sum;
}

int mainDiag(int data[100][100], int n) {

	int i, sum;
	sum = 0;

	for (i = 0; i < n; i++) {
		sum += data[i][i];
	}

	return sum;
}


int main() {

	int data[100][100];
	int n, i, k, sum;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		for (k = 0; k < n; k++) {
			scanf("%d", &data[i][k]);
		}
	}

	sum = secondDiag(data, n);

	printf("the sum: %d", sum);

	return 0;
}