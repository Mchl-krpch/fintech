/*
  task: you have input array and pointers with indicating to add a number to a certain range
  text: perform operations on the array as quickly as possible and output it

 input: array capacity, number of changes, array in line
output: changed array
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void change_array (long long *array, int capacity, int **changes, int how_much_to_change);
void change_array (long long *array, int capacity, int **changes, int how_much_to_change) {
	assert (array);
	assert (changes);

	long long *plus_array = (long long *)calloc (capacity, sizeof (long long));
	  // #6 filling array (place boarders)
	for (int cur_change = 0; cur_change < how_much_to_change; cur_change++) {
		plus_array[changes[cur_change][0]] += changes[cur_change][2];
		if (changes[cur_change][1] + 1 < capacity) {
			plus_array[changes[cur_change][1] + 1] -= changes[cur_change][2];
		}
	}

	  // #7 add array
	for (int index = 1; index < capacity; index++) {
		plus_array[index] += plus_array[index - 1];
	}
	for (int index = 0; index < capacity; index++) {
		array[index] += plus_array[index];
	}
	return;
}

int main () {
	  // #1 input
	int capacity = 0;
	int transformations = 0;
	scanf ("%d %d", &capacity, &transformations);
	  // #2 creating array
	long long *array = (long long *)calloc (capacity, sizeof (long long));
	assert (array);
	for (int index = 0; index < capacity; index++) {
		scanf ("%lld", array + index);
	}

	  // #3 create change-base
	int **changes = (int **)calloc (capacity, sizeof (int *));
	assert (changes);
	for (int index = 0; index < transformations; index++) {
		*(changes + index) = (int *)calloc (3, sizeof (int));
		assert (*(changes + index));
		for (int ind = 0; ind < 3; ind++) {
			scanf ("%d", &changes[index][ind]);
		}
	}

	  // #4 algo
	change_array (array, capacity, changes, transformations);

	  // #5 output
	for (int index = 0; index < capacity; index++) {printf ("%lld ", *(array + index));}
	free (array);
	for (int index = 0; index < transformations; index++) {
		free (*(changes + index));
	}
	free (changes);
}
/*
algorithm comment:
we place labels in several places in a separately
created array that will indicate how much the next
and all subsequent cells will differ relative to
the previous cells, after which the array is passed
through with the addition of the previous cell
to the next
*/