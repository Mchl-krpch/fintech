#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct vector {
	void *data;
	size_t size;
	size_t capacity;
	size_t elem_size;
};

struct vector *vector_new (size_t elems, size_t elem_size) {
	struct vector *v = (struct vector *)malloc (sizeof (struct vector));
	assert (v);

	v->data = malloc (elems * elem_size);
	assert (v->data);

	v->size = elems;
	v->capacity = elems;
	v->elem_size = elem_size;

	return v;
}

int vector_push (struct vector *v, void const *elem) {
	assert (v);
	assert (elem);

	if (v->data == NULL)
		return 1;

	if (v->size == v->capacity) {
        v->data = realloc (v->data, ((v->capacity * 2) + 1) * v->elem_size);
        if (v->data == NULL)
			return 1;
		v->capacity = (v->capacity * 2) + 1;
    }

	memcpy ((char *)v->data + v->elem_size * v->size++, elem, v->elem_size);

	return 0;
}

int vector_empty (struct vector const *v) {
	assert (v);

	if (v->size == 0)
		return 1;

	return 0;
}

struct vector *vector_delete (struct vector *v) {
	assert (v);

	free (v->data);
	free (v);
	
	return NULL;
}

void vector_print (struct vector const *v, void (*pf)(void const *data)) {
	assert (v);
	
	printf("[");
    if (v->size) {
        pf ((char *)v->data + v->elem_size * (0));
        for (size_t cur = 1; cur < v->size; cur++) {
			printf(", ");
            pf ((char *)v->data + cur * v->elem_size);
        }
    }
    printf("]\n");

	return;
}

int vector_set (struct vector *v, size_t index, void const *elem) {
	assert (v);
	assert (elem);

	if (!(index < v->size))
        return 1;

	memcpy ((char *)v->data + index * v->elem_size, elem, v->elem_size);

	return 0;
}

int vector_get (struct vector const *v, size_t index, void *elem) {
	assert (v);
	assert (elem);

	if (!(index < v->size))
        return  1;

	if (v->data == NULL)
		return 1;

	memcpy (elem, (char *)v->data + index * v->elem_size, v->elem_size);

	return 0;
}

int vector_resize (struct vector *v, size_t new_size) {
	assert (v);

	if (v->data == NULL)
		return 1;

	if (new_size > v->capacity) { 
		v->data = realloc ((char *)v->data, new_size * v->elem_size);
		if (v->data == NULL) 
			return 1;
		v->capacity = new_size;
	}
	v->size = new_size;

	return 0;
}

int vector_pop (struct vector *v, void *elem) {
	assert (v);
	assert (elem);

	if (v->size == 0)
		return 1;

	memcpy (elem, (char *)v->data + v->elem_size * --v->size, v->elem_size);

	if (v->size <= v->capacity / 4) {
        vector_resize (v, v->size);
	}

	return 0;
}

size_t vector_size (struct vector const *v) {return v->size;}