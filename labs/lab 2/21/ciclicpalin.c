/*
	This program checks whether a string is a cyclic palindrome.

	Author: Viorel Rînja
*/


#include <stdlib.h>
#include <stdio.h>

int circularPosition(int num, int divider) {
	/*
		Making operations on 1d array simulate a circular one,
		by using congruence modulo operation
	*/

	//In this context, divider is the (mod b)
	if (num < 0) {
		//If negative, add up the divider till the first pozitive value
		num += (-num/divider + 1) * divider; 
	} else {
		//if positive, get the remainder of dividing by divider
		num = num % divider;
	}

	return num;
}

int isPalindrome(char data[], int leftWall, int rightWall, int bound) {
	//Given an array and bounds, check palindromity within these bounds

	/*
		Compare the leftmost and the righrmost elements
		(narrowing the distance between the walls till a certain center element).
		If the elements are not equal, the sequence is not a
		palindrome.
	*/

	int leftMost, rightMost;

	//s
	for (int i = 0; i <= (rightWall - leftWall) / 2; i++) {
		// printf("\nIndex :%d\n", i);
		leftMost = circularPosition(leftWall + i, bound);
		rightMost = circularPosition(rightWall - i, bound);

		if (data[leftMost] != data[rightMost]) {
			return 0;
		}
	}

	return 1;
}

int stepCounter(int data[], int n) {
	int i;

	//Getting the minimum amount of steps (right or left)
	for (i = 0; i < n; i++) {
		if (data[i]) {
			return i;
		}
		if (data[n-1-i]) {
			return i;
		}
	}
}

int main () {

	char data[200];
	int palindromePos[200];
	int n, i, leftWall, rightWall;

	scanf("%d", &n);

	for (i = 0; i < n; i++){
		scanf("%d", &data[i]);
	}

	for (i = 0; i < n; i++) {
		printf("%d ", palindromePos[i]);
	}
	printf("\n");

	printf("%d", stepCounter(palindromePos, n));

	return 0;
}