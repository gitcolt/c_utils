#include "input.h"
#include "../raw_input/raw_input.h"

#include <stdio.h>
#include <unistd.h>

void input_init() {
    enable_raw_input();
}

void debug_print_key(enum Key key) {
    switch (key) {
        case KEY_UNKNOWN: printf("KEY_UNKNOWN\r\n"); break;
        case KEY_A:       printf("KEY_A\r\n");       break;
        case KEY_B:       printf("KEY_B\r\n");       break;
        case KEY_C:       printf("KEY_C\r\n");       break;
        case KEY_D:       printf("KEY_D\r\n");       break;
        case KEY_E:       printf("KEY_E\r\n");       break;
        case KEY_F:       printf("KEY_F\r\n");       break;
        case KEY_G:       printf("KEY_G\r\n");       break;
        case KEY_H:       printf("KEY_H\r\n");       break;
        case KEY_I:       printf("KEY_I\r\n");       break;
        case KEY_J:       printf("KEY_J\r\n");       break;
        case KEY_K:       printf("KEY_K\r\n");       break;
        case KEY_L:       printf("KEY_L\r\n");       break;
        case KEY_M:       printf("KEY_M\r\n");       break;
        case KEY_N:       printf("KEY_N\r\n");       break;
        case KEY_O:       printf("KEY_O\r\n");       break;
        case KEY_P:       printf("KEY_P\r\n");       break;
        case KEY_Q:       printf("KEY_Q\r\n");       break;
        case KEY_R:       printf("KEY_R\r\n");       break;
        case KEY_S:       printf("KEY_S\r\n");       break;
        case KEY_T:       printf("KEY_T\r\n");       break;
        case KEY_U:       printf("KEY_U\r\n");       break;
        case KEY_V:       printf("KEY_V\r\n");       break;
        case KEY_W:       printf("KEY_W\r\n");       break;
        case KEY_X:       printf("KEY_X\r\n");       break;
        case KEY_Y:       printf("KEY_Y\r\n");       break;
        case KEY_Z:       printf("KEY_Z\r\n");       break;
        case KEY_UP:      printf("KEY_UP\r\n");      break;
        case KEY_DOWN:    printf("KEY_DOWN\r\n");    break;
        case KEY_LEFT:    printf("KEY_LEFT\r\n");    break;
        case KEY_RIGHT:   printf("KEY_RIGHT\r\n");   break;
        case KEY_SPACE:   printf("KEY_SPACE\r\n");   break;
        case KEY_ENTER:   printf("KEY_ENTER\r\n");   break;
    }
}

enum Key read_key() {
    static char buf[3];

    ssize_t nbytes = read(STDIN_FILENO, &buf, 3);
    if (nbytes == 3) {
        if (buf[0] == '\033' && buf[1] == '[') {
            switch (buf[2]) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
            }
        }
    }
    else if (nbytes == 1) {
        char ch = buf[0];
        if (ch >= 0x41 && ch <= 0x5A)
            return ch - 0x41;
        if (ch >= 0x61 && ch <= 0x7A)
            return ch - 0x61;
    }
    return KEY_UNKNOWN;
}
