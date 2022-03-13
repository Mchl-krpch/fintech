/*
task: You have two arrays
text: You have to find intersection of these two arrays

 input: capacity of first array, capacity of second array, array n.1, array n.2
output: intersection-array
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int find_intersection (int *arr1, int *arr2, int capacity, int *answer) {
    assert (arr1);
    assert (arr2);

    int answer_id = 0;
    int id1 = 0;
    int id2 = 0;

    while (1) {
        if (arr1[id1] == arr2[id2]) {
            answer[answer_id] = arr1[id1];
            answer_id++;
            id1++;
            id2++;

            if (id1 == capacity) {break;}
            if (id2 == capacity) {break;}
            continue;
        }
        if (arr1[id1] > arr2[id2]) {
            id2++;
            if (id2 == capacity) {break;}
            continue;
        }
        if (arr1[id1] < arr2[id2]) {
            id1++;
            if (id1 == capacity) {break;}
            continue;
        }
    }
    return answer_id;
}

int main () {
        // #1 input data
    int capacity_1 = 0;
    int capacity_2 = 0;
    scanf ("%d %d", &capacity_1, &capacity_2);

        // #2 filling arrays
    int *arr1 = (int *)calloc (capacity_1, sizeof (int));
    assert (arr1);
    for (int ind = 0; ind < capacity_1; ind++) {scanf ("%d", arr1 + ind);}
    int *arr2 = (int *)calloc (capacity_2, sizeof (int));
    assert (arr2);
    for (int ind = 0; ind < capacity_2; ind++) {scanf ("%d", arr2 + ind);}

        // #3 algo
    int answer_capacity = 0;
    int *answers = (int *)calloc (10, sizeof (int));
    assert (answers);
    if (capacity_2 > capacity_1) {answer_capacity = find_intersection (arr1, arr2, capacity_2, answers);}
    else {answer_capacity = find_intersection (arr1, arr2, capacity_1, answers);}

        // #4 output answer
    for (int index = 0; index < answer_capacity; index++) {printf ("%d ", answers[index]);}
    
    free (arr1);
    free (arr2);
}
/*
algorithm comment:
since the arrays are already sorted, we find equal elements using
two pointers, in case of inequality of elements at their address

algo: O(N)
memo: O(N)
*/