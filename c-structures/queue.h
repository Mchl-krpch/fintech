#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct queue {
	long long elem_size;
	long long size;
	long long capacity;

	long long head;
	long long tail;

	void *data;
};

static inline void *byte_address_of (long long index, struct queue *q) {return (void *)((char *)q->data + (index * q->elem_size));}

struct queue *queue_new (size_t elem_size) {
	struct queue* q = (struct queue *)calloc (1, sizeof (struct queue));
	assert (q);

	q->data = malloc (1 * elem_size);
	assert (q->data);

	q->head = 0;
	q->tail = 0;
	q->size = 0;

	q->elem_size = elem_size;
	q->capacity = 1;

	return q;
}

int queue_empty (struct queue const *q) {
	assert (q);
	
	if (q->size == 0)
		return 1;

	return 0;
}

struct queue *queue_delete (struct queue *q) {
	assert (q);

	free (q->data);
	free (q);

	return NULL;
}

void queue_print (struct queue const *q, void (*pf)(void const *data)) {    
	assert (q);

	printf ("[");
	if (q->size != 0) {
		for (int index = 0; index < q->size - 1; index++){
			pf ((char *)q->data + (q->head - 1) * q->elem_size - q->elem_size * index);
			printf (", ");
		}
		pf ((char *)q->data + (q->head - 1) * q->elem_size - q->elem_size * (q->size - 1));
	}
	printf ("]\n");
	
	return;
}

int queue_push (struct queue *q, const void *elem) {
	assert (q);
	assert (elem);

	if (q->size > q->capacity)
		return 1;

	if (q->size == q->capacity - 1) {
		q->data = realloc (q->data, (q->capacity * 2 + 1) * q->elem_size);

		if (q->data == NULL)
			return 1;

		q->capacity = q->capacity * 2 + 1;
	}

	memcpy ((char *)q->data + q->head++ * q->elem_size, elem, q->elem_size);
	q->size++;

	return 0;
}


int queue_pop (struct queue *q, void *elem) {
	assert (q);
	assert (elem);

	if (q->size == 0)
		return 1;

	if (q->tail >= (q->size / 2) + 1) {
		for (int index = 0; index < q->size; index++)
			memcpy (byte_address_of (index, q), byte_address_of (index + q->tail, q), q->elem_size);

		q->head -= q->tail;
		q->tail = 0;
	}

	memcpy (elem, (char *)q->data + q->tail++ * q->elem_size, q->elem_size);
	q->size--;

	return 0;
}