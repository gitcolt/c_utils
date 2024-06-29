#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>

static struct termios old_termios;

void disable_raw_input();

static void sigint_handler(int sig_num) {
    disable_raw_input();
    signal(SIGINT, SIG_DFL);
    raise(SIGINT);
}

void disable_raw_input() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
}

void enable_raw_input() {
    if (tcgetattr(STDIN_FILENO, &old_termios) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    struct termios raw_termios = old_termios;
    raw_termios.c_iflag &= ~(
            ICRNL |                  // fix ctrl-m
            IXON
            );                       // disable ctrl-s and ctrl-q
    raw_termios.c_oflag &= ~(OPOST); // disable post-processing output, specifically,
                                     // converting "\n" to "\r\n"
    raw_termios.c_lflag &= ~(
            ECHO |
            ICANON |
            IEXTEN                   // disable ctrl-v (literal prefix)
            );
    // raw_termios.c_cc[VMIN] = 0;      // min bytes for read()
    // raw_termios.c_cc[VTIME] = 1;     // read() timeout in 100ms multiples

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }

    atexit(disable_raw_input);
    signal(SIGINT, sigint_handler);
}
