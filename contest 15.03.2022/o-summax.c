/*
  task: given two arrays
  text: you need to find the largest sum, which consists of two 
        numbers from different arrays, moreover, the index of the first
        term is less than or equal to the index of the second

 input: capacity of array and two arrays
output: two indexs (value from first and second array)
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void find_max_i_before_equiv_j (int *array_1, int *array_2, int capacity, int *answer);
void find_max_i_before_equiv_j (int *array_1, int *array_2, int capacity, int *answer) {
    assert (array_1);
    assert (array_2);
    assert (answer);

    int summax = 0;
    int save_i = 0;
    int ind_1  = 0;
    int ind_2  = 0;
    int max_1  = 0;

      // #4 search maximum
    for (int index = 0; index < capacity; index++) {
        if (max_1 < array_1[index]) {
            max_1 = array_1[index];
            save_i = index;
        }
        if (max_1 + array_2[index] > summax) {
            summax = max_1 + array_2[index];
            ind_2 = index;
            ind_1 = save_i;
        }
    }
    *(answer) = ind_1;
    *(answer + 1) = ind_2;

    return;
}

int main () {
      // #1 input
    int capacity = 0;
    scanf ("%d", &capacity);

      // #2 reading arrays
    int *array_1 = (int *)calloc (capacity, sizeof (int));
    assert (array_1);
    for (int ind = 0; ind < capacity; ind++) {
        scanf ("%d", array_1 + ind);
    }
    int *array_2 = (int *)calloc (capacity, sizeof (int));
    assert (array_2);
    for (int ind = 0; ind < capacity; ind++) {
        scanf ("%d", array_2 + ind);
    }

      // #3 output
    int *answer = (int *)calloc (2, sizeof (int));
    find_max_i_before_equiv_j (array_1, array_2, capacity, answer);
    printf ("%d %d\n", *(answer), *(answer + 1));

    free (answer);
    free (array_2);
    free (array_1);
}
/*
algorithm comment:
at each step, we look to see if the number from the first array is greater than what was
found in the previous step and at each step we compare the element from the second array
with the largest number found at this and previous steps from the first array
*/