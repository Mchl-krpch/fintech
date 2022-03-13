/*
task: you have array of coins
text: find minimal sum which you couldn't have of this array

 input: array of coins (all coins are different) {A_1 <= A_2 ... <= A_n}
output: minimal cost
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int comp (const int *A, const int *B) {
	return *A - *B;
}

int find_min_sum (int *coins, int capacity) {
	assert (coins);

	  // #4 sort array
	qsort(coins, capacity, sizeof (int), (int(*) (const void *, const void *)) comp);

	  // #5 beginning of the search
	int maximum_available_amount = 0;
	int pivot = 0;

	while (*(coins + pivot) - maximum_available_amount < 2) {
		maximum_available_amount += coins[pivot];
		if (pivot == capacity - 1) {break;}
		pivot++;
	}

	return maximum_available_amount + 1;
}

int main () {
		// #1 input data
	int coins_number = 0;
	scanf ("%d", &coins_number);

		// #2 fill array
	int *coins = (int *)calloc (coins_number, sizeof (int));
	assert (coins);
	for (int cur_coin = 0; cur_coin < coins_number; cur_coin++) {scanf ("%d", coins + cur_coin);}

		// #3 apply algo
	printf ("%d\n", find_min_sum (coins, coins_number));
	
	free (coins);
}
/*
algorithm comment:
algorithm compares max_sum in current step with next coins[pivot]
to see if the difference with the pivot is too big

[algorithm previously sorts coins by qsort]
algo: O(N)
memo: O(N)
*/