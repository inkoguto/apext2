#ifndef WINDOWS_H
#define WINDOWS_H
#include <ncurses.h>

WINDOW * create_footer();

WINDOW * create_mainwin();

void create_content_window(char * content);

#endif