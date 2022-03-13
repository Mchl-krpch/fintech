/*Babichev-contest-1
	a-change
	the machine must give change to all those in need in five-ruble coins, and users make payments in coins of 5, 10, 50, 100
	In order for everyone to have enough, you need to fully know the input of the task and be able to find the number of 5
	ruble coins that will be required for delivery
	
	 input: 1str: n of purchases
			2str: [1st buyer sum, 2nd buyer sum, 3rd...]
	
	output: number of 5-ruble coins
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int algo (unsigned n_purchases, unsigned *payment) {
	assert (payment);

	int   five = 0;   // minus 5 rubles
	int result = 0;   // result sum

		// #4 sum all numbers & count 5-conins
	for (unsigned purchase = 0; purchase < n_purchases; purchase++) {
		if (payment[purchase] == 5) {five++;}
		else {
			five -= ((payment[purchase] / 5) - 1);
			if (five < 0) {
				result -= five;
				five = 0;
			}
		}
	}
	return result; 
}

int main () {
		// #1 input
	unsigned n_purchases = 0;
	scanf ("%u", &n_purchases);
		// #2 array input
	unsigned *payment = (unsigned *)calloc (n_purchases, sizeof (unsigned));
	assert (payment);
	for (unsigned purchase = 0; purchase < n_purchases; purchase++) {scanf ("%u", (payment + purchase));}

		// #3 call inline
	int result = algo (n_purchases, payment);

		// #5 output
	printf ("%d", result);

	free (payment);
}
/*
essence of the algorithm:
add all the numbers, counting fives, then use the formula
result = (SUM / 5) - n_of_fives
and check and check if the answer is yes
	
algo: O(N)
memo: O(1)
*/