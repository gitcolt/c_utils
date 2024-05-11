#ifndef ERR_H
#define ERR_H

void _print_err(const char *msg,
                const char *filename,
                int line_num,
                const char *func_name,
                ...);

void _print_warn(const char *msg,
                const char *filename,
                int line_num,
                const char *func_name,
                ...);

// ', ##' elides the comma if __VA_ARGS__ is empty
// See https://gcc.gnu.org/onlinedocs/gcc-4.6.4/gcc/Variadic-Macros.html
#define PRINT_ERR(msg, ...) \
    _print_err(msg, __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define PRINT_WARN(msg, ...) \
    _print_warn(msg, __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#endif // end ERR_H

#ifdef ERR_IMPL

#include "ansi_colors.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

enum LVL {
    WARN,
    ERR,
};

static void print_line_info(const char *msg,
                            enum LVL lvl,
                            const char *filename,
                            int line_num,
                            const char *func_name,
                            ...) {
    va_list args;
    va_start(args, func_name);

    char buf[1024];
    const char *col = lvl == ERR ? RED_TXT : YEL_TXT;
    strcpy(buf, col);
    strncat(buf, "[%s:%d:%s]: ", 1024 - strlen(col));
    fprintf(stderr, buf, filename, line_num, func_name);
    vfprintf(stderr, msg, args);
    fprintf(stderr, RST_COL);
    fflush(stderr);

    va_end(args);
}

void _print_err(const char *msg,
                const char *filename,
                int line_num,
                const char *func_name,
                ...) {
    va_list args;
    va_start(args, func_name);

    print_line_info(msg, ERR, filename, line_num, func_name, args);

    va_end(args);
}

void _print_warn(const char *msg,
                const char *filename,
                int line_num,
                const char *func_name,
                ...) {
    va_list args;
    va_start(args, func_name);

    print_line_info(msg, WARN, filename, line_num, func_name, args);

    va_end(args);
}

#endif
