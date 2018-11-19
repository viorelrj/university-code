#include <stdio.h>
#include <stdlib.h>

int main () {

	int n, i, counter = 0;
	int *data;


	scanf("%d", &n);

	data = (int*)calloc(n, sizeof(int));

	for (i = 0; i < n; i++) {
		scanf("%d", &data[i]);
	}

	for (i = 0; i < n - 1; i++) {
		if (data[i] * data[i + 1] < 0)
			counter++;
	}

	printf("%d", counter);

	return 0;
}