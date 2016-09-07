#ifndef tomtix_PARTITION_H
#define tomtix_PARTITION_H

typedef struct t_partition_ t_partition;

t_partition *t_partition_new(size_t n);
void t_partition_destroy(t_partition *);

// representative of x in partition p
int t_partition_rep(t_partition*, int x);

// tells if x and y are equivalent
int t_partition_equal(t_partition*, int x, int y);

// set x and y to be equivalent
void t_partition_union(t_partition*, int x, int y);


#endif // tomtix_PARTITION_H
