#include <ncursesw/ncurses.h>
#include <locale.h>
#include "footer.h"
#include "superblock.h"
#include "dir.h"

void print_intro(WINDOW * window, int posX, int posY);

WINDOW * create_main_window() {
    WINDOW * window = newwin(LINES, COLS, 0, 0);
	WINDOW *info_win = NULL;
	int ch = 0;
	keypad(window, TRUE);
	wbkgdset(window, COLOR_PAIR(2));
	wclear(window);
    box(window, 0, 0);
    wrefresh(window);
	info_win = get_footer(window);
		
	print_intro(window, 2, 1);

	while (ch != KEY_F(12)) {
		ch = wgetch(window);
		if (ch == KEY_F(1)) {
			create_dir_window();
		}
		if (ch == KEY_F(2)) {
			render_superblock(window, 0, 0, COLS, LINES-3);
		}
	}

	delwin(info_win);
    
    return window;
}

void print_intro(WINDOW * window, int posX, int posY) {
	mvwprintw(window, posY, posX, "F1 - przeglądaj pliki");
	mvwprintw(window, posY+1, posX, "F2 - przeglądaj supeblock");
	mvwprintw(window, posY+2, posX, "F3 - przeglądaj deskryptor grupy");
}
