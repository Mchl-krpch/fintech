/*
task: you have array of elements
text: you have to find maxsum in this array

 input: array
output: maxsum
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long calc_max_sub_array_sum (int *array, int capacity) {
	assert (array);

	long long maxsum = -999999999;
	long long cur_sum = array[0];
	maxsum = cur_sum;
	for (int index = 1; index < capacity; index++) {
		if (cur_sum + array[index] < 0) {cur_sum = array[index];}
		else {
			if (cur_sum + array[index] < array[index]) {cur_sum = array[index];}
			else {cur_sum += array[index];}
		}
		if (cur_sum > maxsum) {maxsum = cur_sum;}
	}

	return maxsum;
}

int main () {
		// #1 input
	int capacity = 0;
	scanf ("%d", &capacity);

		// #2 creating
	int *array = (int *)calloc (capacity, sizeof (int));
	assert (array);
	for (int ind = 0; ind < capacity; ind++) {scanf ("%d", array + ind);}

		// algo
	printf ("%lld\n", calc_max_sub_array_sum (array, capacity));

	free (array);
}
/*
algorithm comment:
the algorithm goes through the array, keeping the current sum at this step,
if it is less than zero, we start counting it again. in other cases, we
continue to add new values

algo: O(N)
memo: -
*/