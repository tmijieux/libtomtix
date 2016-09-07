#include <stdlib.h>
#include "tomtix/partition.h"

typedef struct t_partition_ {
    size_t size;
    int *parent;
    int *weight;
} t_partition;

t_partition *
t_partition_new(size_t n)
{
    t_partition *p = malloc(sizeof(*p));
    p->size = n;
    p->parent = malloc(sizeof(int) * n);
    p->weight = calloc(sizeof(int), n); // zero'd
    for (unsigned i = 0; i < n; i++)
        p->parent[i] = i;
    return p;
}

void t_partition_destroy(t_partition *p)
{
    free(p->parent);
    free(p->weight);
    free(p);
}

int t_partition_rep(t_partition *p, int x)
{
    int y = x;
    while (p->parent[y] != y) {
        y = p->parent[y];
    }
    int z = x;
    do {
        z = p->parent[x];
        p->parent[x] = y;
        x = z;
        // ON ÉCRASE LES ARBRES! BORDEL!
    } while (x != y);
    return y;
}

int t_partition_equal(t_partition *p, int x, int y)
{
    return (t_partition_rep(p, x) == t_partition_rep(p, y));
}

void t_partition_union(t_partition *p, int x, int y)
{
    int a = t_partition_rep(p, x);
    int b = t_partition_rep(p, y);
    
    if (p->weight[a] > p->weight[b]) {
        p->parent[b] = a;
    } else if (p->weight[a] < p->weight[b]) {
        p->parent[a] = b;
    } else {
        p->parent[a] = b;
        p->weight[b] ++;
    }
}
