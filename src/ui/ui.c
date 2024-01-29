#include <ncurses.h>
#include <stdlib.h>
#include "entity.h"
#include "inode.h"
#include "footer.h"
#include "file_content.h"
#include "dir.h"


struct DirList * get_root_dir();

void handle_list(struct DirList * dir_list, WINDOW * window);

void render_list(struct DirList * dir, struct Entity* active, WINDOW * window);

struct DirList * switch_directory(int inode_idx);

void initialize();

void ui() {
	WINDOW *info_win = NULL;
	WINDOW *mainwin = NULL;

	initialize();
	mainwin = create_dir_window();
	info_win = get_footer();
	diplay_files(mainwin);
	delwin(mainwin);
	delwin(info_win);
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

