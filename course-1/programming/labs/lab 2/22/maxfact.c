/*

	This program checks which prime number has the biggest frequence of occurance
	from the factored representation of primes

	Author: Viorel Rinja
*/

#include <stdio.h>
#include <stdlib.h>


//Checking primality by getting modulus to every previous number
int isPrime(int number) {
	int i;
	for (i = 2; i < ((number / 2) + 1); i++) {
		if (number % i == 0) {
			return 0;
		}
	}

	return 1;
}

struct primeNumCount {
	int number;
	int counter;
};

int main () {
	//The number of primes, having the conditions, will not exceed 2000
	struct primeNumCount primes[2000];
	int number, i, maxOcPrime, maxOcTimes;
	int index = 0;

	scanf("%d", &number);

	for (i = 2; i <= number; i++) {
		if (isPrime(i)){
			//If is prime, add it to the array with prime numbers and their frequency
			primes[index].number = i;
			primes[index].counter = 0;

			index++;

		}
	}

	for (i = 0; i < index; i++){
		while (number % primes[i].number == 0){
			//If can divide by prime, divide the number, and increment the count of occurance
			//of the prime
			primes[i].counter++;
			number = number / primes[i].number;
		}
	}

	maxOcTimes = 0;
	maxOcPrime = primes[0].number;

	//Checking the maximum occurance of the prime number
	for (i = 0; i < index; i++){
		if (primes[i].counter >= maxOcTimes) {
			maxOcTimes = primes[i].counter;
			maxOcPrime = primes[i].number;
		}
	}

	printf("%d ", maxOcPrime);

	return 0;
}