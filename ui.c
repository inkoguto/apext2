#include <ncurses.h>
#include <stdlib.h>
#include "dir.h"
#include "inode.h"

struct DirList * get_root_dir();

void handle_list(struct DirList * dir_list);

void render_list(struct DirList * dir);

void show_info(struct Dir * dir);

struct DirList * switch_directory(int inode_idx);

void ui() {
	struct DirList * dir_list = get_root_dir();
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	
	handle_list(dir_list);
	cleanup(dir_list->head);
	free(dir_list);

	clear();
	endwin();
}

void render_list(struct DirList * dir_list) {
	Inode * inode;
	struct Dir * dir = dir_list->head;
	while (dir != NULL) {
		inode = get_inode(dir->inode);
		printw("%s %10d\n", dir->name, inode->i_mode);
		dir = dir->next;
		free(inode);
	}
}

void handle_list(struct DirList * dir_list) {
	struct Dir * dir = dir_list->head;
	struct DirList * new_dir_list = NULL;
	int inodex_idx = 0;
	int posX = 0, posY = 0, ch = 0;
	char * esc_info = "Nacisnij F10 aby wyjsc";

	render_list(dir_list);
	mvprintw(LINES-1, 0, "%s", esc_info);
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
			inodex_idx = dir->inode;
			if (new_dir_list != NULL) {
				cleanup(new_dir_list->head);
				free(new_dir_list);
			}
			new_dir_list = switch_directory(inodex_idx);
			dir = new_dir_list->head;
			posX = 0;
		}
		if (ch == KEY_F(10)) {
			cleanup(dir);
			free(new_dir_list);
			return;
		}
		move(posX, posY);
		refresh();
	}
}

struct DirList * switch_directory(int inode_idx) {
	Inode * inode = get_inode(inode_idx);
	struct DirList * dir_list = get_dir_data(inode);

	render_list(dir_list);

	
	free(inode);

	return dir_list;
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