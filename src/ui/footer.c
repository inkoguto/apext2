#include <ncurses.h>


WINDOW * get_footer(WINDOW * window) {
	WINDOW * info_window = NULL;
	char * esc_info = "Nacisnij F10 aby wyjsc | F3 to view file";
	int width = COLS;
	int height = 3;
	int posX = LINES - 3;
	int posY = 0;

	info_window = subwin(window, height, width, posX, posY);
	
	wbkgdset(info_window, COLOR_PAIR(3));
    wclear(info_window);
	box(info_window, 0, 0);
	mvwprintw(info_window, 1, 1, "%s", esc_info);
	wrefresh(info_window);

	return info_window;
}