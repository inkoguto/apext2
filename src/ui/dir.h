#ifndef DIR_H
#define DIR_H
#include <ncurses.h>

WINDOW * create_dir_window();

void display_files(WINDOW * window);

#endif