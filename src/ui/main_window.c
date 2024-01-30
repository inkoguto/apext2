#include <ncurses.h>
#include "footer.h"
#include "dir.h"

WINDOW * create_main_window() {
    WINDOW * window = newwin(LINES, COLS, 0, 0);
	WINDOW *info_win = NULL;
	WINDOW *mainwin = NULL;

    mainwin = create_dir_window();
	info_win = get_footer();
    display_files(mainwin);

	delwin(mainwin);
	delwin(info_win);
    
    return window;
}