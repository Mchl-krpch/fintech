#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define STD_ADD 111
typedef long long unsigned set_t;

struct set {
	set_t capacity;
	set_t size;

	void *data;
};

static inline set_t calculate_add (set_t key) {
    for (set_t add = 0; add < 64; add++) {if (key == ((set_t)1 << add)) {return add;}}
    return STD_ADD;
}

struct set *set_new (size_t capacity) {
	struct set *s = (struct set *)calloc (1, sizeof (struct set));

	s->data = calloc (sizeof (set_t), (capacity >> 6) + 1);
	s->capacity = capacity;
	s->size = 0;

	return s;
}

int set_insert (struct set *s, size_t elem) {
	assert (s);

	if (elem >= s->capacity)
		return 1;
	
	set_t position = elem >> 6; 

	set_t save_s = *((set_t *)s->data + position);
	*((set_t *)s->data + position) |= ((set_t)1 << (elem - (position << 6)));

	if (save_s == *((set_t *)s->data + position))
		return 1;

	s->size++;

	return 0;
}

int set_erase (struct set *s, size_t elem) {
	assert (s);

	if (elem >= s->capacity)
		return 1;
	
	set_t position = elem >> 6;

	set_t save_s = *((set_t *)s->data + position);
	*((set_t *)(s->data) + position) &= (UINT64_MAX) - ((set_t )1 << (elem - (position << 6)));

	if (save_s == *((set_t*)s->data + position)) {
		return 1;
	}

	s->size--;

	return 0;
}


int set_find (struct set const *s, size_t elem) {
	assert (s);

	if (elem >= s->capacity) {
		return 0;
	}

	return ((set_t)1 << (elem % 64)) & (*((set_t *)s->data + (elem / 64)));
}

struct set *set_delete (struct set *s) {
	assert (s);

	free(s->data);
	free(s);

	return NULL;
}

int set_empty (struct set const *s) {
	assert (s);

	if (s->size == 0)
		return 0;

	return 1;
}

ssize_t set_findfirst (struct set const *s, size_t start) {
	assert (s);

    set_t position = start >> 6;
    set_t remainder = start - (position << 6); 

    set_t first_b = ((*((set_t*)(s->data) + position) >> remainder) << remainder);

    if ((first_b ^ (first_b - 1)) & first_b) {return (ssize_t)(calculate_add ((first_b ^ (first_b - 1)) & first_b)) + (position << 6);}

    for (set_t* byte = ((set_t*)(s->data) + position + 1); byte < ((set_t*)s->data + (s->capacity / 64) + 1); byte++) {if ((*byte ^ (*byte - 1)) & *byte) {return (ssize_t)((((byte - ((set_t*)s->data + position)) + position) << 6) + calculate_add ((*byte ^ (*byte - 1)) & *byte));}}

    return -1;
}

size_t set_size (struct set const *s) {
	assert (s);
	return (size_t)s->size;
}

void set_print (struct set const *s) {
	assert (s);

	printf("[");
	if (s->size) {
		int first = 0;
		if (*((set_t*)s->data + (0 >> 6)) & ((set_t)1 << 0)) {
			printf ("%d", 0);
			first = 1;
		}

		for (set_t number = 1; number < s->capacity; number++) {
			if (*((set_t*)s->data + (number >> 6)) & ((set_t)1 << (number % 64))) {
				if (first) {
					printf(", ");
				}
				first = 1;

				printf("%llu", number);
			}
		}
	}
	printf ("]\n");
}