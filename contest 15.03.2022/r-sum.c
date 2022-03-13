/*
  task: you have array of numbers and examples
  text: you have to figure out if there is a subarray of the original array whose sum equals the number from the array

 input: array of numbers, array of samples
output: indexes of "not found"
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN -2147483648

static int comp(const void* A, const void* B) {return *(const int *)A >= *(const int *)B;}
void find_sums (int *arr, int capacity, int *samples, int sums_to_search, int *ind1, int *ind2) {
    assert (arr);
    assert (samples);
    assert (ind1);
    assert (ind2);

        // #4 sort array
    qsort (arr, capacity, sizeof(int), comp);
    for (int cur_sum_ind = 0; cur_sum_ind < sums_to_search; cur_sum_ind++) {
        int first  = MIN;
        int second = MIN;

        int left = 0;
        int right = capacity - 1;

            // #5 find sum
        while (left != right) {
            long long sum = (long long)arr[left] + arr[right];

            if (sum < *(samples + cur_sum_ind))
                left++;
            else if (sum > *(samples + cur_sum_ind))
                right--;
            else {
                second = *(arr + right);
                first  = *(arr + left);
                break;
            }
        }

            // #6 fill answer arrays
        if ((second == MIN) && (first == MIN)) {ind1[cur_sum_ind] = MIN;}
        else {
            if (first < second) {
                ind1[cur_sum_ind] = first;
                ind2[cur_sum_ind] = second;
            }
            else {
                ind1[cur_sum_ind] = second;
                ind2[cur_sum_ind] = first; 
            }
        }
    } 
}

int main() {
      // #1 input
    int capacity = 0;
    int sums_to_search = 0;
    scanf ("%d %d", &capacity, &sums_to_search);

      // #2 fill arr
    int *arr = (int *)calloc (sizeof (int), capacity);
    assert (arr);
    for (int index = 0; index < capacity; index++) {
        scanf("%d", arr + index);
    }

      // #2 fill arr
    int *samples = (int *)calloc (sizeof (int), sums_to_search);
    assert (arr);
    for (int index = 0; index < sums_to_search; index++) {
        scanf("%d", samples + index);
    }

      // #3 start sorting
    int *ind1 = (int *)calloc (sizeof (int), sums_to_search);
    assert (arr);
    int *ind2 = (int *)calloc (sizeof (int), sums_to_search);
    assert (arr);
    find_sums (arr, capacity, samples, sums_to_search, ind1, ind2);

    for (int index = 0; index < sums_to_search; index++) {
        if (ind1[index] == MIN) {
            printf("Not found\n");
        }
        else {
            printf ("%d %d\n", ind1[index], ind2[index]);
        }
    }

    free (ind1);
    free (ind2);
    free (samples);
    free (arr);
}
/*
algorithm comment:
sort the array and start searching with "two pointers" if the
sum is not found - put -1 in the value of the first index and thus
we can understand when to display the message "not found"

algo: O(NlogN*M)
memo: O(N)
*/