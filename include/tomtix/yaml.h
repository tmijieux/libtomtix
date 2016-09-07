#ifndef t_YAML_H
#define t_YAML_H

#include <glib.h>

typedef enum t_yaml_type_ {
    TX_YAML_LIST = 10,
    TX_YAML_TABLE = 13,
    TX_YAML_SCALAR = -9
} t_yaml_type;

typedef struct t_yaml_ {
    t_yaml_type type;
    union {
        GList *list;
        GHashTable *table;
        char *scalar;
        void *value;
    };
} t_yaml;

t_yaml *t_yaml_new_from_file(char const *file_name);
void t_yaml_dump(FILE *out, t_yaml const *yaml);
void t_yaml_free(t_yaml *yaml);
    
#endif // t_YAML_H
