#include <stdio.h>
#include <stdlib.h>

int main () {
	int n, i, checkpoint, sum = 0;
	int *data;

	scanf("%d", &n);

	data = (int*)calloc(n, sizeof(int));

	for (i = 0; i < n; i++) {
		scanf("%d", &data[i]);
	}

	for (i = 0; i < n; i++) {
		if (data[i] <  0)
			checkpoint = i+1;
		break;
	}

	for (i = checkpoint; i < n; i++) {
		sum += data[i];
	}

	printf("%d\n", sum);

	return 0;
}