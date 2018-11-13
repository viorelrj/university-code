/*

	This program gets the biggest number from a sequence and
	displays it, including the number of its occurance.

	Author: Viorel Rinja
	
*/


#include <stdlib.h>
#include <stdio.h>

int n, current, max, counter, delta;

int main () {

	//Reading the list size and first element
	scanf("%d", &n);
	printf("Checking the numbers\n");
	scanf("%d", &current);
	
	//Initializing the list
	max = current;
	counter = 1;

	//As the first item has already been read, the loop skips it.
	for (int i = 1; i < n; i++) {
		//Reading the next element
		scanf("%d", &current);

		if (current > max) {
			max = current;
			counter = 1;
		} else if (current == max) {
			counter++;
		}

		// //Setting the max value, according to mathematical formula
		// max = (current + max + abs(current - max)) * 0.5;

		// //if the current number was bigger, than it became equal to max
		// //thus, its difference will be 0;
		// //for any other case, current - max is strictly negative, thus
		// //the difference && 1 will be 0
		// delta = ((current - max) && 1);

		// //So if we flip the delta, we will get the case only when the
		// //max has been changed

		// //If the biggest number hasn't changed, increment the counter
		// counter = (counter * !delta) + 1;
	}

	printf("%d %d\n", max, counter);

	return 0;
}
