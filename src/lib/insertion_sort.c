#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tomtix/sorting.h"

void t_insertion_sort(void *buf,
                           size_t nmemb, size_t size,
                           int (*compare)(void*,void*))
{
    for (unsigned i = 0; i < nmemb; ++i) {
        unsigned j = i;
        
        while (j > 0 && compare(buf+j*size,buf+(j-1)*size) < 0) {
            uint8_t tmp[size];
            memcpy(tmp, buf+(j-1)*size, size);
            memcpy(buf+(j-1)*size, buf+j*size, size);
            memcpy(buf+j*size, tmp, size);
            -- j;
        }
    }
}
