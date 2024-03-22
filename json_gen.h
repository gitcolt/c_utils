#ifndef JSON_GEN_H
#define JSON_GEN_H

void jg_init_context();
void jg_start();
void jg_end();
void jg_obj_start(char *key);
void jg_obj_end();
void jg_obj_key_val_int(char *key, int val);
void jg_obj_key_val_str(char *key, char *val);
void jg_print();
void jg_write_to_file(const char *filename);
void jg_int(char *key, int val);
void jg_str(char *key, char *val);
void jg_arr_start(char *key);
void jg_arr_end();
void jg_arr_item_int(int val);
void jg_arr_item_str(char *val);
void jg_destroy();

#endif

#ifdef JSON_GEN_IMPL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct JGContext {
    char *str;
    int indent;
} JGContext;

static JGContext ctx;

void increase_indent() {
    ctx.indent += 2;
}

void decrease_indent() {
    ctx.indent -= 2;
}

void indent() {
    for (int i = 0; i < ctx.indent; ++i)
        strcat(ctx.str, " ");
}

void jg_start() {
    ctx.str = malloc(999);
    ctx.indent = 0;

    jg_obj_start(NULL);
}

void jg_end() {
    int i = strlen(ctx.str);
    ctx.str[i - 2] = ' ';

    decrease_indent();

    indent();

    strcat(ctx.str, "}\n");
}

void jg_destroy() {
    free(ctx.str);
}

void jg_obj_start(char *key) {
    indent();
    if (key) {
        char buf[99];
        sprintf(buf, "\"%s\": {\n", key);
        strcat(ctx.str, buf);
    }
    else
        strcat(ctx.str, "{\n");

    increase_indent();
}

void jg_obj_end() {
    int i = strlen(ctx.str);
    ctx.str[i - 2] = ' ';

    decrease_indent();

    indent();

    strcat(ctx.str, "},\n");
}

void jg_obj_key_val_int(char *key, int val) {
    char buf[99];

    indent();

    sprintf(buf, "\"%s\": %d,\n", key, val);
    strcat(ctx.str, buf);
}

void jg_obj_key_val_str(char *key, char *val) {
    indent();

    char buf[99];
    sprintf(buf, "\"%s\": \"%s\",\n", key, val);
    strcat(ctx.str, buf);
}

void jg_print() {
    printf("%s\n", ctx.str);
}

void jg_write_to_file(const char *filename) {
    FILE *f;
    if ((f = fopen(filename, "w")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fwrite(ctx.str, 1, strlen(ctx.str), f);
}

void jg_int(char *key, int val) {
    indent();

    char buf[99];
    sprintf(buf, "\"%s\": \"%d\",\n", key, val);
    strcat(ctx.str, buf);
}

void jg_str(char *key, char *val) {
    indent();

    char buf[99];
    sprintf(buf, "\"%s\": \"%s\",\n", key, val);
    strcat(ctx.str, buf);
}

void jg_arr_start(char *key) {
    indent();

    char buf[99];
    sprintf(buf, "\"%s\": [\n", key);
    strcat(ctx.str, buf);

    increase_indent();
}

void jg_arr_end() {
    int i = strlen(ctx.str);
    ctx.str[i - 2] = ' ';

    decrease_indent();
    indent();
    strcat(ctx.str, "],\n");
}

void jg_arr_item_int(int val) {
    indent();

    char buf[99];
    sprintf(buf, "%d,\n", val);
    strcat(ctx.str, buf);
}

void jg_arr_item_str(char *val) {
    indent();

    char buf[99];
    sprintf(buf, "%s,\n", val);
    strcat(ctx.str, buf);
}

#endif
