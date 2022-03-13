/*
task: you should find max-square on the histogram
text: max square

 input: capacity, array of colums-lens
output: square value
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//####Stack-part############################
struct stack {
	void *data;
	int size;
	int capacity;
	size_t elem_size;
};

struct stack *stack_new (size_t elem_size) {
	struct stack *st = (struct stack *)malloc (sizeof (struct stack));
	assert (st);
	st->data = malloc (elem_size);
	st->size = 0;
	st->capacity = 1;
	st->elem_size = elem_size;
	return st;
}

int stack_push (struct stack *st, const void *elem) {
	assert (st);
	assert (elem);
	if (st->data == NULL)
		return 1;

	if (st->size == st->capacity) {
		st->data = realloc(st->data, 2 * st->capacity * st->elem_size);
		st->capacity *= 2;
	}
	memcpy ((char *)st->data + st->elem_size * st->size, elem, st->elem_size);
	++st->size;
	return 0;
}

int stack_pop (struct stack *st, void *elem) {
	assert (st);
	assert (elem);
	if (st->size == 0)
		return 1;
	memcpy (elem, (char *)st->data + st->elem_size * (st->size - 1), st->elem_size);
	--st->size;
	return 0;
}

int stack_top (struct stack *st, void *elem) {
	assert (st);
	assert (elem);
	if (st->size == 0)
		return 1;
	memcpy(elem, (char *)st->data + st->elem_size * (st->size - 1), st->elem_size);
	return 0;
}

int stack_empty(struct stack const *st) {
	assert (st);
	if (st->size == 0)
		return 1;
	return 0;
}

struct stack *stack_delete(struct stack *st) {
	assert (st);
	free (st->data);
	free (st);
	
	return NULL;
}

void stack_clear (struct stack *st) {
	st->size = 0;
	return;
}
//####Stack-part############################

long long calculate_square (int *arr, int capacity) {
	assert (arr);

		// #3 left boarders array
	int *next_left = (int *)calloc (capacity, sizeof (int));
	assert (next_left);
	
		// #4 fill left boarders array
	struct stack *stack = stack_new (sizeof (int));
	int top = 0;
	for (int index = 0; index < capacity; index++) {
		while (!stack_empty (stack)) {
			stack_top (stack, &top);
			if (arr[top] >= arr[index]) {
				stack_pop (stack, &top);
			}
			else {break;}
		}

		if (stack_empty (stack)) {next_left[index] = -1;}
		else                     {stack_top (stack, &next_left[index]);}

		stack_push (stack, &index);
	}
	stack_clear (stack);

		// #4 fill right boarders array
	int *next_right = (int *)calloc (capacity, sizeof (int));
	for (int index = capacity - 1; index >= 0; index--) {
		while (!stack_empty (stack)) {
			stack_top (stack, &top);

			if (arr[top] >= arr[index]) {stack_pop (stack, &top);}
			else                        {break;}

		} 
		if (stack_empty (stack)) {next_right[index] = capacity;}
		else                     {stack_top (stack, &next_right[index]);}
		
		stack_push (stack, &index);
	}

		// #5 calculate square
	long long square = 0;
	for (int index = 0; index < capacity; index++) {
		long long cur_square = (long long)(next_right[index] - next_left[index] - 1) * arr[index];
		if (cur_square > square) {square = cur_square;}
	}

	stack = stack_delete (stack);
	free (next_left);
	free (next_right);

	return square;
}

int main () {
		// #1 input array
	int capacity = 0;
	scanf ("%d", &capacity);
	int *arr = (int *)calloc (capacity, sizeof (int));
	assert (arr);
	for (int index = 0; index < capacity; index++) {scanf ("%d", arr + index);}
	
		// #2 algo
	printf ("%lld\n", calculate_square (arr, capacity));

	free (arr);
}
/*
algorithm comment:
The whole algorithm is based on finding the left and right
boundaries of different heights in the array, the process is
implemented through the stack and the top of the stack
subsequently ends up in a special array of either right
or left boundaries, the maximum area
is calculated by definition

algo: O(N)
memo: O(N)
*/