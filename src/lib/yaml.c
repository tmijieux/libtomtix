#include <stdio.h>
#include <yaml.h>
#include <assert.h>
#include <stdbool.h>

#include "tomtix/error.h"
#include "tomtix/yaml.h"
#include "tomtix/stack.h"
#include "tomtix/compiler.h"

static void
hashtable_dump_cb(gpointer key_name, gpointer field, gpointer out_stream)
{
    fprintf(out_stream, "%s: ", (char*)key_name);
    t_yaml_dump((FILE*) out_stream, (t_yaml*) field);
}

void t_yaml_dump(FILE *out, t_yaml const *yaml)
{
    switch (yaml->type) {
    case TX_YAML_LIST:
	fprintf(out, "yaml list start:\n");
        GList *l = yaml->list;
        while (l != NULL) {
	    t_yaml_dump(out, (t_yaml*) l->data);
            l = l->next;
	}
	fprintf(out, "yaml list end\n");
	break;
    case TX_YAML_TABLE:
	fprintf(out, "yaml table start:\n");
	g_hash_table_foreach(yaml->table, hashtable_dump_cb, out);
	fprintf(out, "yaml table end\n");
	break;
    case TX_YAML_SCALAR:
	fprintf(out, "%s\n", yaml->scalar);
	break;
    }
}

static void
insert_in_container(t_yaml *cont, char const *keyname, t_yaml *yaml)
{
    switch (cont->type) {
    case TX_YAML_TABLE:
        g_hash_table_insert(cont->table, g_strdup(keyname), yaml);
        break;
    case TX_YAML_LIST:
        cont->list = g_list_append(cont->list, yaml);
        break;
    default:
        t_error("invalid container\n");
        break;
    }
}

static t_yaml*
wrap(t_yaml_type type, void *value)
{
    t_yaml *yaml = malloc(sizeof*yaml);
    yaml->type = type;
    yaml->value = value;
    if (yaml->type == TX_YAML_SCALAR)
        yaml->value = strdup(value);
    return yaml;
}

static void
push_container(t_stack *s, t_yaml_type type,
               char const *keyname, void *value)
{
    t_yaml *yaml = wrap(type, value);
    if (t_stack_size(s) > 0) {
        t_yaml *cont = t_stack_head(s);
        insert_in_container(cont, keyname, yaml);
    }
    t_stack_push(s, yaml);
}

#define CLEAR_STRING(s) do { g_free(s); s = NULL; } while(0)

t_yaml*
t_yaml_new_from_file(char const *filepath)
{
    FILE *f = NULL;
    yaml_parser_t parser;
    t_yaml *yaml = NULL, *tmp;
    t_stack *container_stack = t_stack_new();

    f = fopen(filepath, "r");
    if (f == NULL) {
	t_error("%s: %s\n", filepath, strerror(errno));
	return NULL;
    }
    memset(&parser, 0, sizeof parser);
    if (!yaml_parser_initialize(&parser)) {
        fclose(f);
        t_error("Failed to initialize yaml parser!\n");
        yaml_parser_delete(&parser);
	return NULL;
    }
    yaml_parser_set_input_file(&parser, f);

    bool done = false;
    while (!done) {
        GHashTable *table;
        char *keyname = NULL;
        yaml_event_t event;

        memset(&event, 0, sizeof event);
	if (!yaml_parser_parse(&parser, &event)) {
	    printf("Yaml parser error %d\n", parser.error);
            yaml_event_delete(&event);
            break;
	}

	switch (event.type) {
	case YAML_DOCUMENT_END_EVENT:
        case YAML_STREAM_END_EVENT:
            done = true;
        case YAML_MAPPING_END_EVENT:
	case YAML_SEQUENCE_END_EVENT:
            if (t_stack_size(container_stack))
                yaml = t_stack_pop(container_stack);
            CLEAR_STRING(keyname);
	    break;
	case YAML_SEQUENCE_START_EVENT:
	    push_container(container_stack, TX_YAML_LIST, keyname, NULL);
            CLEAR_STRING(keyname);
	    break;
	case YAML_MAPPING_START_EVENT:
            table = g_hash_table_new_full(
                g_str_hash, g_str_equal, g_free, (GDestroyNotify)t_yaml_free);
	    push_container(container_stack, TX_YAML_TABLE, keyname, table);
            CLEAR_STRING(keyname);
	    break;
	case YAML_SCALAR_EVENT: {
            char *value = g_strdup((char*) event.data.scalar.value);
            if (t_stack_size(container_stack) > 0) {
                t_yaml *head = t_stack_head(container_stack);
                if (head->type == TX_YAML_TABLE && keyname == NULL)
                    keyname = value;
                else {
                    tmp = wrap(TX_YAML_SCALAR, value);
                    insert_in_container(head, keyname, tmp);
                    CLEAR_STRING(keyname);
                }
	    } else { // the whole document IS a scalar:
                yaml = wrap(TX_YAML_SCALAR, value);
                CLEAR_STRING(keyname);
            }
	    break;
        }
	default:
	    break;
	}
	yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    while (t_stack_size(container_stack))
        yaml = t_stack_pop(container_stack);
    t_stack_delete(container_stack);
    fclose(f);
    return yaml;
}

void t_yaml_free(t_yaml *yaml)
{
    if (yaml == NULL)
        return;

    switch (yaml->type) {
    case TX_YAML_TABLE:
        g_hash_table_destroy(yaml->table);
        break;
    case TX_YAML_LIST:
        g_list_free_full(yaml->list, (GDestroyNotify) t_yaml_free);
        break;
    case TX_YAML_SCALAR:
        free(yaml->scalar);
        break;
    }
    free(yaml);
}
