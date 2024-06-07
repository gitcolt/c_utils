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

#endif
