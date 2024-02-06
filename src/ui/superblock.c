#include <ncurses.h>
#include "fs_metadata.h"

void render_superblock(WINDOW * parent_window, int posX, int posY, int width, int height) {
    WINDOW * sb_block = newwin(height, width, posY, posX);
    struct Superblock * sb = get_superblock();

	wbkgdset(sb_block, COLOR_PAIR(2));
	wclear(sb_block);
    box(sb_block, 0, 0);
    wrefresh(sb_block);    
}