/*
task: you have brackets subsequence
text: you have to figure out if each parenthesis finds a closing pair in the file

 input: subsequence
output: bool answer is close
*/
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//########stack adds##########
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
	if (st->data == NULL) {return 1;}
	if (st->size == st->capacity) {
		st->data = realloc(st->data, 2 * st->capacity * st->elem_size);
		st->capacity *= 2;
	}
	memcpy ((char *)st->data + st->elem_size * st->size, elem, st->elem_size);
	++st->size;
	return 0;
}

int stack_pop (struct stack *st, void *elem) {
	if (st->size == 0) {return 1;}
	memcpy (elem, (char *)st->data + st->elem_size * (st->size - 1), st->elem_size);
	--st->size;
	return 0;
}

int stack_top (struct stack *st, void *elem) {
	if (st->size == 0) {return 1;}
	memcpy (elem, (char *)st->data + st->elem_size * (st->size - 1), st->elem_size);
	return 0;
}

int stack_empty (struct stack const *st) {
	if (st->size == 0)
		return 1;
	return 0;
}

struct stack *stack_delete (struct stack *st) {
	free (st->data);
	free (st);

	return NULL;
}
//########stack adds##########

bool is_close (struct stack *st) {
	assert (st);

	char ch = (char)getchar ();
	do {
		if (ch == '<' || ch == '(' || ch == '{' || ch == '[') {stack_push (st, &ch);}
		else if (st->size == 0) {return false;}
		else {
			char tmp;
				// 
			switch (ch) {
				case '>': {
					stack_top(st, &tmp);
					if (tmp == '<') {stack_pop(st, &tmp);}
					else {return false;}
					break;
				}
				case ')': {
					stack_top (st, &tmp);
					if (tmp == '(') {stack_pop (st, &tmp);}
					else {return false;}
					break;
				}
				case '}': {
					stack_top (st, &tmp);
					if (tmp == '{') {stack_pop (st, &tmp);}
					else {return false;}
					break;
				}

				case ']': {
					stack_top(st, &tmp);
					if (tmp == '[') {stack_pop (st, &tmp);}
					else {return false;}
					break;
				}

				default: return false;
			}
		}
		ch = (char)getchar ();
	} while (ch != '\n');

	if (stack_empty (st)) {return true;}
	else {return false;}
}

int main() {
	  // #1 creating stack
	struct stack *st = stack_new (sizeof (char));

	  //algo
	(is_close (st)) ? printf ("YES") : printf ("NO");
	st = stack_delete (st);
}
/*
algorithm comment:
using a stack, we implement a collapsing procedure
-we look at whether the closing symbol of the desired
type lies on the top of the stack or not and
returns a yes / no answer

algo: O(N)
memo: O(N)
*/