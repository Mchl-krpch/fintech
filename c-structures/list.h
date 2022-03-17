#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list {
	long long elem;
	struct list *next;
};

struct list *list_new (int elem) {
	struct list *list = (struct list *)calloc (1, sizeof (struct list));
	assert (list);

	list->elem = elem;

	return list;
}

struct list *list_insert (struct list *head, int elem) {
	if (!head) {return list_new (elem);}

	struct list *save_head = head;
	while (head->next)
		head = head->next;
	head->next = list_new (elem);

	return save_head;
}

struct list *list_find (struct list *head, int elem) {
	if (!head) {return head;}

	while (1) {
		if (head->elem == elem) {return head;}
		if (head->next) {head = head->next;}
		else {break;}
	}

	return NULL;
}

struct list *list_delete (struct list *head) {
	if (!head) {return NULL;}
	
	while (head->next) {
		struct list *save_head = head;
		head = head->next;
		free (save_head);
	}
	free (head);

	return NULL;
}

struct list *list_next (struct list *curr) {
	if (!curr) {return NULL;}
	return curr->next;
}

void list_print (struct list const *head) {
	printf ("[");
	if (head) {
		while (head->next) {
			printf ("%lld, ", head->elem);
			head = head->next;
		}
		printf ("%lld", head->elem);
	}
	printf ("]\n");
}

struct list *list_insert_after (struct list *head, struct list *where, struct list *what) {
	if (!where || !what) {return head;}
	if (!head) {return what;}

	struct list* save_head = head;
	do {
		if (head == where) {
			what->next = head->next;
			head->next = what;
			return save_head;
		}
		if (head->next) {head = head->next;}
		else {break;}
	} while (1);

	return NULL;
}

struct list *list_insert_before (struct list *head, struct list *where, struct list *what) {
	if (!where || !what) {return head;}
	if (!head) {return what;}
	
	if (where == head) {
		what->next = where;
		return what;
	}

	struct list* save_head = head;
	while (head->next) {
		if (head->next == where) {
			head->next = what;
			what->next = where;

			return save_head;
		}
		head = head->next;
	}

	return NULL;
}

struct list *list_erase (struct list *head, int elem) {
	if (!head) {return NULL;}

	if (head->elem == elem) {
		struct list *node = head->next;
		free (head);
		return node;
	}

	struct list *save_head = head;

	while (head->next) {
		if (head->next->elem == elem) {
			struct list *listToDel  = head->next;
			head->next = head->next->next;
			free (listToDel);
			return save_head;
		}
		head = head->next;
	}
 
	return save_head;
}