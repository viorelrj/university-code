#include <stdio.h>
#include <stdlib.h>

int checkBiDigit(int number){
	/*
		Creating a dynamic array with calloc, in order
		to have all cells set to 0
	*/
	int *digits;
	digits = (int*)calloc(10, sizeof(int));

	//Incrementing the counter of the index of the mod of the digit
	//After each mod operation we divide the number by 10
	//In such a way we count the occurance of every digit.
	while (number / 10 != 0) {
		digits[number%10]++;
		number = number / 10;
	}

	//As the highest order digit gives 0 when dividing by 0,
	//We have to repeat this step for it individually
	digits[number%10]++;


	//Setting up the digit counter
	int counter = 0;

	//Count every digit (that is not null)
	for (int i = 0; i < 10; i++)
		if (digits[i])
			counter++;
	

	//Bidigit means that it has only two digits
	//Basically, the number of digits equals to two.
	if (counter == 2)
		return 1;
	else
		return 0;
}


int main() {
	int number;
	scanf("%d", &number);

	int i = 0;

	//Increasing the step size, until finding the first bidigit number
	while(!checkBiDigit(number + i) && !checkBiDigit(number - i)){
		i++;
	}


	//If number is bidigit, show the smallest one
	//The if condition does not process the "else", if the condition is true
	if (checkBiDigit(number - i)){
		printf("%d\n", number - i);
	} else {
		printf("%d\n", number + i);
	}
	

	return 0;
}