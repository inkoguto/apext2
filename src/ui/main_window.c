#include <ncurses.h>
#include "footer.h"
#include "dir.h"

WINDOW * create_main_window() {
    WINDOW * window = newwin(LINES, COLS, 0, 0);
	WINDOW *info_win = NULL;
	int ch = 0;
	keypad(window, TRUE);
	info_win = get_footer(window);
		
	while (ch != KEY_F(12)) {
		ch = wgetch(window);
		if (ch == KEY_F(1)) {
			create_dir_window();
		}
	}

	delwin(info_win);
    
    return window;
}