#include "str_utils.h"

#include <string.h>
#include <ctype.h>

char *ltrim(char *str) {
    while (isspace(*str))
        ++str;
    return str;
}

char *rtrim(char *str) {
    char *p = str + strlen(str) - 1;
    while (isspace(*p) && p > str)
        --p;
    *(p + 1) = '\0';
    return str;
}

char *trim(char *str) {
    return rtrim(ltrim(str));
}

void sb_create(StringBuilder *sb) {
    sb->s = ARR(char, 0);
}

void sb_destroy(StringBuilder *sb) {
    arr_free(sb->s);
}

void sb_append(StringBuilder *sb, const char *str) {
    size_t str_len = strlen(str);
    for (size_t i = 0; i < str_len; ++i)
        ARR_APPEND(sb->s, str[i]);
    sb->str_len = str_len + 1;
}

void sb_build(StringBuilder *sb, char *out) {
    ARR_APPEND(sb->s, '\0');
    strcpy(out, sb->s);
}
