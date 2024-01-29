#include <ncurses.h>
#include <stdlib.h>
#include "entity.h"
#include "inode.h"
#include "footer.h"
#include "file_content.h"
#include "main_window.h"

struct DirList * get_root_dir();

void handle_list(struct DirList * dir_list, WINDOW * window);

void render_list(struct DirList * dir, struct Entity* active, WINDOW * window);

struct DirList * switch_directory(int inode_idx);

void initialize();

void ui() {
	struct DirList * dir_list = get_root_dir();
	WINDOW *info_win = NULL;
	WINDOW *mainwin = NULL;

	initialize();
	mainwin = create_mainwin();
	info_win = get_footer();

	handle_list(dir_list, mainwin);

	if (dir_list->head != NULL) {
		cleanup(dir_list->head);
	}
	
	free(dir_list);
	delwin(mainwin);
	delwin(info_win);
    endwin();
}

void render_list(struct DirList * dir_list, struct Entity* active, WINDOW * window) {
	Inode * inode;
	struct Entity* dir = dir_list->head;
	
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
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	clear();
	refresh();
}

void handle_list(struct DirList * dir_list, WINDOW * window) {
	struct Entity* dir = dir_list->head;
	struct DirList * new_dir_list = NULL;
	char * file_content = NULL;
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
			if (is_directory(dir->inode)) {
				inodex_idx = dir->inode;
				if (new_dir_list != NULL) {
					cleanup(new_dir_list->head);
					free(new_dir_list);
				}
				new_dir_list = switch_directory(inodex_idx);
				dir = new_dir_list->head;
			}
		}
		if (ch == KEY_F(3)) {
			if (is_file(dir->inode)) {
				file_content = get_file_data(get_inode(dir->inode));
				create_content_window(file_content);
				free(file_content);
			}
			if (is_directory(dir->inode)) {
				create_content_window("dir");
			}
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

struct DirList * get_root_dir() {
	Inode * inode = get_first_inode();
	struct DirList * dir = get_dir_data(inode);

	free(inode);
	
	return dir;
}