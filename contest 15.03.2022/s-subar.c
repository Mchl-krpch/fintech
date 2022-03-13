/*
task: array of numbers array of samples
text: need to understand if there is a subarray whose sum is equal to the given example

 input: array of nums and array of samples
output: inds or "not found"
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void search_sum (int capacity, int *arr, int sums_to_search, long long *patterns, int *ans1, int *ans2, int *found) {
    assert (arr);
    assert (patterns);
    assert (ans1);
    assert (ans2);
    assert (found);

    long long *prefix_sum = (long long *)calloc (capacity + 1, sizeof (long long));
    assert (prefix_sum);

        // #4 find prefix sum
    prefix_sum[0] = 0;
    for (int index = 0; index < capacity; ++index) {prefix_sum[index + 1] = prefix_sum[index] + arr[index];}
    for (int cur_sum = 0; cur_sum < sums_to_search; ++cur_sum) {
        int right = 1;
        for (int index = 0; right <= capacity && index <= capacity; ++index) {
            while (right <= capacity && prefix_sum[right] < patterns[cur_sum] + prefix_sum[index]) {++right;}

            if (right == capacity + 1) {break;}
            if (right == index) {continue;}

                // #5 compare
            if (prefix_sum[right] - prefix_sum[index] == patterns[cur_sum]) {
                found[cur_sum] = 1;
                ans1[cur_sum] = index + 1;
                ans2[cur_sum] = right + 1;
                break;
            }
        }
    }
    free(prefix_sum);
}

int main() {
        // #1 input array
    int capacity = 0;
    int sums_to_search = 0;
    scanf("%d %d", &capacity, &sums_to_search);
    int* arr = (int *)calloc(capacity, sizeof(int));
    assert (arr);
    for (int index = 0; index < capacity; ++index) {scanf("%d", arr + index);}

        // #2 samples input
    long long* patterns = (long long *)calloc(sums_to_search, sizeof(long long));
    assert (patterns);
    for (int index = 0; index < sums_to_search; ++index) {scanf("%lld", &patterns[index]);}

        // #3 input answers
    int* ans1 = (int *)calloc (sums_to_search, sizeof(int));
    assert (ans1);
    int* ans2 = (int *)calloc (sums_to_search, sizeof(int));
    assert (ans2);
    int* found = (int *)calloc (sums_to_search, sizeof(int));
    assert (found);

        // #6 algo
    search_sum (capacity, arr, sums_to_search, patterns, ans1, ans2, found);

        // #7 out
    for (int index = 0; index < sums_to_search; ++index) {
        if (found[index]) {printf ("%d %d\n", ans1[index], ans2[index]);}
        else              {printf ("Not found\n");}
    }
    //=================================================
    free (found);
    free (ans1);
    free (ans2);
    free (arr);
    free (patterns);
    
    return 0;
}
/*
algorithm comment:
looking for prefix sums and comparing them with the value of the example
like in prev task

algo: O(NN)
memo: O(N)
*/