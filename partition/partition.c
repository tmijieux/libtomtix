#include <stdlib.h>
#include "partition.h"

struct partition {
    size_t size;
    int *parent;
    int *weight;
};

struct partition *partition_create(size_t n)
{
    struct partition *p = malloc(sizeof*p);
    p->size = n;
    p->parent = malloc(sizeof(int) * n);
    p->weight = calloc(sizeof(int), n); // zero'd
    for (int i = 0; i < n; i++)
        p->parent[i] = i;
    return p;
}

void partition_destroy(struct partition *p)
{
    free(p->parent);
    free(p->weight);
    free(p);
}

int partition_representative(struct partition *p, int x)
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

int partition_equivalence(struct partition *p, int x, int y)
{
    return (partition_representative(p, x)
            == partition_representative(p, y));
}

void partition_union(struct partition *p, int x, int y)
{
    int a = partition_representative(p, x);
    int b = partition_representative(p, y);
    if (p->weight[a] > p->weight[b]) {
        p->parent[b] = a;
    } else if (p->weight[a] < p->weight[b]) {
        p->parent[a] = b;
    } else {
        p->parent[a] = b;
        p->weight[b] ++;
    }
}
