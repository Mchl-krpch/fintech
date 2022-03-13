/*
task: you have two arrays
text: you need to derive their symmetrical difference

 input: two arrays
output: array of symmetrical difference
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define capacity 100000
static int comp (const void *i, const void *j) {return *(const int *)i - *(const int *)j;}

int find_difference (int *arr1, int *arr2, int cap1, int cap2, int *answer) {
	assert (arr1);
	assert (arr2);
	
		// #6 sort arrays
	qsort ((void *)arr1, cap1, sizeof (int), comp);
	qsort ((void *)arr2, cap2, sizeof (int), comp);

		// #7 we inc. index of array, which contain lower value at this step
		// and write it in array of answer
	int ans_ind = 0;
	while (*arr1 != 0 && *arr2 != 0) {
		if (*arr1 < *arr2) {
			answer[ans_ind] = *arr1;
			ans_ind++;
			arr1++;
		}
		else if (*arr1 > *arr2) {
			answer[ans_ind] = *arr2;
			ans_ind++;
			arr2++;
		}
			// #8 we skip equiv values
		else if (*arr1 == *arr2) {
			arr1++;
			arr2++;
		}
			// #9 the array may end, and then we are forced
			// to completely output the remainder of the other
		if (*arr1 == 0 && *arr2 != 0) {
			while (*arr2 != 0) {
				answer[ans_ind] = *arr2;
				ans_ind++;
				arr2++;
			}
		}
		if (*arr2 == 0 && *arr1 != 0) {
			while (*arr1 != 0) {
				answer[ans_ind] = *arr1;
				ans_ind++;
				arr1++;
			}
		}
	}

	return ans_ind;
}

int main () {
		// #1 array n.1 creating
	int cap1 = 0;
	int *arr1 = (int *)calloc (capacity, sizeof (int));
	assert (arr1);
	int *save1 = arr1;

		// #2 array n.2 creating
	int cap2 = 0;
	int *arr2 = (int *)calloc (capacity, sizeof (int));
	assert (arr2);
	int *save2 = arr2;
	
		// #3 array n.1 input
	int cur_num = -1;
	int size1 = 0;
	while (cur_num != 0) {
		scanf ("%d", &cur_num);
		if (cur_num != 0) {arr1[size1] = cur_num;}
		size1++;
	}
	cap1 = size1 - 1;

		// #4 array n.2 input
	cur_num = -1;
	int size2 = 0;
	while (cur_num != 0) {
		scanf ("%d", &cur_num);
		if (cur_num != 0) {arr2[size2] = cur_num;}
		size2++;
	}
	cap2 = size2 - 1;

		// #5 start searching difference
	int *answer = (int *)calloc (cap1 + cap2 + 1, sizeof (int));
	assert (answer);
	int ans_ind = find_difference (arr1, arr2, cap1, cap2, answer);

	for (int index = 0; index < ans_ind; index++) {printf ("%d ", answer[index]);}

	free (save1);
	free (save2);
	free (answer);
}
/*
algorithm comment:
order the values in the arrays and write to the response array only
in case of inequality at the current step, an element that is less than
the other. We skip equal values

algo: O(N*logN)
memo: O(N)
*/