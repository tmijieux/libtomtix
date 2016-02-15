#ifndef TREAP_H
#define TREAP_H

struct treap;

typedef int (*treap_compare_f)(void *, void*);

struct treap *treap_create(size_t max_size, treap_compare_f compare_fun);
int treap_insert(struct treap *t, void *value);
int treap_search(struct treap *t, void *value, struct list **ret);
void treap_free(struct treap *t);

#endif //TREAP_H
