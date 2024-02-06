#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include "entity.h"
#include "inode.h"
#include "footer.h"
#include "file_content.h"
#include "dir.h"
#include "main_window.h"

void initialize();

void ui() {
	WINDOW * mainwindow = NULL;
	setlocale(LC_ALL, "");
	initialize();
	mainwindow = create_main_window();

	delwin(mainwindow);
    endwin();
}


void initialize() {
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	curs_set(0);
	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	clear();
	refresh();
}

