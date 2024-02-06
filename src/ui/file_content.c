#include <ncurses.h>
#include "scroll.h"

void create_content_window(char * content) {
    WINDOW * outer;
    WINDOW * inner;
    int  inner_height, inner_width, outer_height, outer_width;

    outer_height = LINES - 5;
    outer_width = COLS - 3;

    inner_height = outer_height - 3;
    inner_width = outer_width - 3;

    outer = newwin(outer_height, outer_width, 1, 2);
    inner = newwin(inner_height, inner_width, 3, 4);

    keypad(inner, TRUE);
    wbkgdset(outer, COLOR_PAIR(1));
    wclear(outer);
    box(outer, 0, 0);
    box(inner, 0, 0);
    wrefresh(outer);

    wbkgdset(inner, COLOR_PAIR(4));
    wclear(inner);
    wrefresh(inner);
    scroll_text(outer, inner, content);
    delwin(outer);
    delwin(inner);
}