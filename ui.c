#include <ncurses.h>
#include <stdlib.h>
#include "dir.h"
#include "inode.h"

struct DirList * get_root_dir();

void render_list();

void show_info(struct Dir * dir);

void ui() {
	struct DirList * dir_list = get_root_dir();
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	render_list(dir_list);
	getch();
	endwin();
	cleanup(dir_list->head);
}

void render_list(struct DirList * dir_list) {
	struct Dir * dir = dir_list->head;
	int posX = 0, posY = 0, ch = 0;
	Inode * inode;

	while (dir != NULL) {
		printw("%s %10d\n", dir->name, dir->inode);
		dir = dir->next;
	}
	dir = dir_list->head;
	move(posX, posY);
	while (ch != KEY_F(10)) {
		ch = getch();
		if (ch == KEY_UP) {
			if (dir->prev != NULL) {		
				posX--;
				dir = dir->prev;
			}	
		}
		if (ch == KEY_DOWN) {
			if (dir->next != NULL) {
				posX++;
				dir = dir->next;
			}
		}
		if (ch == 10) {
			clear();
			inode = get_inode(dir->inode);
			render_list(get_dir_data(inode));
		}
		move(posX, posY);
		refresh();
	}
}

void show_info(struct Dir * dir) {
	WINDOW *info_window;
	info_window = newwin(20, 30, 0, 0);
	wprintw(info_window, "%d", dir->inode);
	wrefresh(info_window);
	wgetch(info_window);
	delwin(info_window);
}

struct DirList * get_root_dir() {
	Inode * inode = get_first_inode();
	struct DirList * dir = get_dir_data(inode);

	free(inode);
	
	return dir;
}