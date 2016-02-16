#ifndef TREAP_H
#define TREAP_H

struct treap;
typedef int (*treap_compare_f)(void *, void*);

#include "list.h"

struct treap *treap_create(treap_compare_f compare_fun);
size_t treap_size(const struct treap*);
int treap_insert(struct treap *t, void *value);
int treap_search(struct treap *t, void *value, struct list **ret);
void treap_free(struct treap *t);

#endif //TREAP_H
