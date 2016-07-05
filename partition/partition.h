#ifndef PARTITION_H
#define PARTITION_H

struct partition;

struct partition *partition_create(size_t n);
void partition_destroy(struct partition *);

// representative of x in partition p
int partition_representative(struct partition*, int x);

// tells if x and y are equivalent
int partition_equivalence(struct partition*, int x, int y);

// set x and y to be equivalent
void partition_union(struct partition*, int x, int y);


#endif //PARTITION_H
