#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stack {
	int size;
	int capacity;
	size_t elem_size;

	void *data;
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
		st->data = realloc (st->data, 2 * st->capacity * st->elem_size);
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

	memcpy (elem, (char *)st->data + st->elem_size * (st->size - 1), st->elem_size);

	return 0;
}

int stack_empty (struct stack const *st) {
	assert (st);

	if (st->size == 0)
		return 1;

	return 0;
}

struct stack *stack_delete (struct stack *st) {
	assert (st);
	
	free (st->data);
	free (st);
	
	return NULL;
}

void stack_print (struct stack const *st, void (*pf)(void const *st)) {
	assert (st);

	printf ("[");
	for (int elem = 0; elem < st->size; elem++) {
		pf ((char *)st->data + elem * st->elem_size);
		if (elem != st->size - 1) {
				printf (", ");
		}
	}
	printf ("]\n");
	
	return;
}