/*
	This is a program to generate array of random numbers, based on
	Linear Congruental Generator, but probably worsened by a group of
	monkeys (from FAF-181) trained to push random buttons on keyboard.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
	Calculate the power by squaring method

	This method uses the binary form to represent the exponent.
	In such a way, using the property of adding up the exponents on
	a multiplication of similar bases.

	IE: 2^5 = 2^1 * 2^4 or, using binary notation for exponent:
	2^(101), which is similar to 2^(1 * 2^0) * 2^(0 * 2^1) * 2^(1 * 2^2)
*/

int getPower(int base, int exp) {
	//initializing the result
	int result = 1;
	for (;;)
	{
		//If most-right digit is 1, we add up the exponent
		if (exp & 1)
			result *= base;
		//Cutting the number from right, to check the greater degree digit
		exp >>= 1;
		//Checking if there still exists a digit
		if (!exp)
			break;
		//Incrementing the digit of exponent (2^(n+1))
		base *= base;
	}

	return result;
}

// function that calculates the next rand number
int getRand(int previous) {
	int m = getPower(2, 14);
	//In order to get rid of repetition, the a and c variables
	//are changed with every generation, thus modifying the formula itself
	unsigned int a = 8121 + getPower(previous, 2);
	unsigned int c = 28411 + getPower(previous, 3);
	unsigned int succesor = (a * previous + c) % m;

	return succesor;
}

int main()
{
	FILE *f, *g;
	int i, randNum;
	time_t seconds;

	seconds = time(NULL);
	f = fopen("generated.txt","w");
	g = fopen("predicted.txt","w");
	randNum = seconds % getPower(2, 14);
	fprintf(f, "%d", randNum);
	for(i = 0; i <= 101; i++) {
		randNum = getRand(randNum);
		// randNum = rand();
		if (i == 101) fprintf(g, "%d", randNum);
		else fprintf(f, " %d", randNum);
	}
	fclose(f);
	fclose(g);

	return 0;
}
