#ifndef STR_UTILS_H
#define STR_UTILS_H

#include "../type_agnostic_dynamic_array/dyn_arr.h"

#include "string.h"

// rtrim() and trim() modify the string in-place
char *ltrim(char *str);
char *rtrim(char *str);
char *trim(char *str);

typedef struct {
    char *s;
    size_t str_len;
} StringBuilder;

void sb_create(StringBuilder *sb);
void sb_destroy(StringBuilder *sb);
void sb_append(StringBuilder *sb, const char *str);
void sb_build(StringBuilder *sb, char *out);

#endif
