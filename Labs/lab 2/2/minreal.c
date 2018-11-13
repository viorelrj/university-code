/*

	This program gets the smallest number from a sequence and
	displays it, including the number of its occurance.

	Author: Viorel Rinja
	
*/


#include <stdlib.h>
#include <stdio.h>

int n, counter;
float current, min, delta;

int main () {

	//Reading the list size and first element
	scanf("%d", &n);
	scanf("%f", &current);
	
	//Initializing the list
	min = current;
	counter = 1;

	//As the first item has already been read, the loop skips it.
	for (int i = 1; i < n; i++) {
		//Reading the next element
		scanf("%f", &current);

		if (current < min) {
			min = current;
			counter = 0;
		} else if (current = min) {
			counter++;
		}

		// //Setting the min value, according to mathematical formula
		// min = (current + min - abs(current - min)) * 0.5;

		// //if the current number was bigger, than it became equal to max
		// //thus, its difference will be 0;
		// //for any other case, current - max is strictly negative, thus
		// //the difference && 1 will be 0
		// delta = ((min - current) && 1);

		// //So if we flip the delta, we will get the case only when the
		// //max has been changed

		// //If the biggest number hasn't changed, increment the counter
		// counter = (counter * !delta) + 1;
	}

	printf("%f %d\n", min, counter);

	return 0;
}
