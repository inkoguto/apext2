#include <ncurses.h>
#include <stdlib.h>
#include "dir.h"
#include "inode.h"

struct DirList * get_root_dir();

void handle_list(struct DirList * dir_list, WINDOW * window);

void render_list(struct DirList * dir, struct Dir * active, WINDOW * window);

WINDOW * show_info();

struct DirList * switch_directory(int inode_idx);

void initialize();

void ui() {
	struct DirList * dir_list = get_root_dir();
	initialize();
    WINDOW *mainwin = newwin(LINES-3, COLS, 0, 0);

	wbkgdset(mainwin, COLOR_PAIR(2));
	wclear(mainwin);
    box(mainwin, 0, 0);
    wrefresh(mainwin); 

	handle_list(dir_list, mainwin);

	if (dir_list->head != NULL) {
		cleanup(dir_list->head);
	}
	
	free(dir_list);
	delwin(mainwin);
    endwin();
}

void render_list(struct DirList * dir_list, struct Dir * active, WINDOW * window) {
	Inode * inode;
	struct Dir * dir = dir_list->head;
	
	wclear(window);
	
	while (dir != NULL) {
		inode = get_inode(dir->inode);
		if (dir->name == active->name) {
			wattron(window, COLOR_PAIR(1));
		} else {
		    wattron(window, COLOR_PAIR(2));
		}
		wprintw(window, "%s %*d\n", dir->name, COLS - 5 - dir->name_len, inode->i_mode);
	
		attroff(COLOR_PAIR(1));
		dir = dir->next;
		free(inode);

		wrefresh(window);
	}
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
	bkgdset(COLOR_PAIR(3));
	clear();
	mvprintw(LINES -2, 10, "Nacisnij F10 aby wyjsc");
	refresh();
}

void handle_list(struct DirList * dir_list, WINDOW * window) {
	struct Dir * dir = dir_list->head;
	struct DirList * new_dir_list = NULL;
	int inodex_idx = 0;
	int ch = 0;

	render_list(dir_list, dir_list->head, window);

	while (ch != KEY_F(10)) {
		ch = getch();
		if (ch == KEY_UP) {
			if (dir->prev != NULL) {		
				dir = dir->prev;
			}	
		}
		if (ch == KEY_DOWN) {
			if (dir->next != NULL) {
				dir = dir->next;
			}
		}
		if (ch == 10) {
			inodex_idx = dir->inode;
			if (new_dir_list != NULL) {
				cleanup(new_dir_list->head);
				free(new_dir_list);
			}
			new_dir_list = switch_directory(inodex_idx);
			dir = new_dir_list->head;
		}
		if (ch == KEY_F(10)) {
			if (new_dir_list != NULL) {
				cleanup(dir);
				free(new_dir_list);
			}
			return;
		}
		if (new_dir_list != NULL) {
			render_list(new_dir_list, dir, window);
		} else {
			render_list(dir_list, dir, window);
		}
	}
}

struct DirList * switch_directory(int inode_idx) {
	Inode * inode = get_inode(inode_idx);
	struct DirList * dir_list = get_dir_data(inode);
	
	free(inode);

	return dir_list;
}

WINDOW * show_info() {
	WINDOW * info_window = NULL;
	info_window = subwin(stdscr, 3, COLS, LINES - 3, 0);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	wbkgdset(info_window, COLOR_PAIR(3));
	char * esc_info = "Nacisnij F10 aby wyjsc";

	mvwprintw(info_window, 0, 0, "%s", esc_info);
	wclear(info_window);
	wrefresh(info_window);
	return info_window;
}

struct DirList * get_root_dir() {
	Inode * inode = get_first_inode();
	struct DirList * dir = get_dir_data(inode);

	free(inode);
	
	return dir;
}