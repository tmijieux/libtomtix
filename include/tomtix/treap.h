#ifndef TREAP_H
#define TREAP_H

typedef struct t_treap_ t_treap;
typedef int (*t_treap_compare_function)(void *, void*);


t_treap *
t_treap_new(t_treap_compare_function compare_fun);

size_t t_treap_size(const t_treap*);
int t_treap_insert(t_treap *t, void *value);
int t_treap_search(t_treap *t, void *value, GList **ret);
void t_treap_free(t_treap *t);

#endif //TREAP_H
