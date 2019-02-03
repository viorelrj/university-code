#include <stdio.h>
#include <stdlib.h>

int main () {
	int n, i, backup;
	int *data;

	scanf("%d", &n);
	data = (int*)calloc(n, sizeof(int));


	for (i = 0; i < n; i++) {
		scanf("%d", &data[i]);
	}

	backup = data[0];

	for (i = 0; i < n - 1; i++) {
		printf("backup: %d \n", backup);
		data[i] = data[i + 1];
	}

	data[n-1] = backup;

	for (i = 0; i < n; i++) {
		printf("%d ", data[i]);
	}


	return 0;
}