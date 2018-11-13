#include <stdio.h>
#include <math.h>

int main() {
	float a, b, c;
	float x1, x2;

	scanf("%f %f %f", &a, &b ,&c);

	float det = b * b - 4 * a * c;

	if (det < 0) {

		printf("The given equation has no real solution");

	} else if (det == 0) {

		x1 = (-b / 2 * a);
		printf("%2.2f", x1);

	} else {
		x1 = (-b - sqrt(det)) / 2 * a;
		x2 = (-b + sqrt(det)) / 2 * a;

		printf("%2.2f %2.2f", x1, x2);
	}

	return 0;
}


