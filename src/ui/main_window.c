#include <ncurses.h>

WINDOW * create_mainwin() {
    WINDOW * mainwin = NULL;
    mainwin = newwin(LINES-3, COLS, 0, 0);

	wbkgdset(mainwin, COLOR_PAIR(2));
	wclear(mainwin);
    box(mainwin, 0, 0);
    wrefresh(mainwin);

    return mainwin;
}
