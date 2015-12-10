#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

int main(int argc, char *argv[])
{
    struct hash_table *ht = ht_create(NULL);
    ht_add_entry(ht, "lulz", "some data", 10);

    int lulz, ret;
    char *buf = ht_get_entry(ht, "lulz", &lulz, &ret);
    printf("%s, %d, %d\n", buf, lulz, ret);

    free(buf);

    ht_free(ht);


    
    
    return EXIT_SUCCESS;
}
