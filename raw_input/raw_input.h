#ifndef RAW_INPUT_H
#define RAW_INPUT_H

void enable_raw_input();
// It's not necessary to call disable_raw_mode() explicitly unless you want to disable
// raw mode before the program exits
void disable_raw_input();

#endif
