/*
task: given the cost of the flute and a set of coins (two of each)
text: You need to know you need to understand whether a person can give the full cost of the flute to the seller

 input: the value of the goods and the denominations of the coins, of which there are two pieces
output: the minimum number of coins, can be exchanged and impossible
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


static int intmin (int left, int right) {return (left < right) ? left : right;}

int calculate (int cost, int capacity, int *coins) {
	assert (coins);

	long long *mask = (long long *)calloc (1 << capacity, sizeof(long long));
	assert (mask);
	mask[0] = 0;

	for (int index = 1; index < (1 << capacity); ++index) {mask[index] = mask[index & (index - 1)] + coins[__builtin_ctz (index)];}
	if (mask[(1 << capacity) - 1] << 1 < cost) {
		free (mask);
		return -2;
	}
	int min_capacity = 2 * capacity + 1;

	for (int union_mask = (1 << capacity) - 1; union_mask >= 0; --union_mask) {
		long long the_rest = cost - mask[union_mask];

		if (the_rest == 0) {min_capacity = intmin (min_capacity, __builtin_popcount (union_mask));}
		if (the_rest < 0) {continue;}

		for (int mask_got_twice = union_mask; mask_got_twice > 0; mask_got_twice &= (mask_got_twice - 1)) {
			if (mask[mask_got_twice] == the_rest) {
				min_capacity = intmin (min_capacity, __builtin_popcount (union_mask) + __builtin_popcount (mask_got_twice));
			}
		}
	}

	free (mask);
	if (min_capacity <= 2 * capacity) {return min_capacity;}
	return -1;
}


int main () {
		// #1 input
	int cost = 0;
	int capacity = 0;
	scanf ("%d %d", &cost, &capacity);

		// #2 fill array
	int *coins = (int *)calloc (capacity, sizeof(int));
	assert (coins);
	for (int index = 0; index < capacity; ++index) {scanf ("%d", coins + index);}
	
		// #2 result
	int result = calculate (cost, capacity, coins);

		// #3 result
	if (result == -2)      {printf ("Impossible\n");}
	else if (result == -1) {printf ("Change\n");}
	else                   {printf ("%d\n", result);}
	
	free (coins);
}