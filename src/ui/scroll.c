#include <ncurses.h>

void scroll_text(
    WINDOW * parent_window,
    WINDOW * window,
    char * content
    ) {
    int lines = 0, content_idx = 0, posX = 0, posY = 0, ch = 0, rows, cols;
    char * p_content = content;
    float progress = 0;


    getmaxyx(window, rows, cols);
    int progressY = cols - 5;
    
    while (*content != '\0') {
        if (*content == '\n') {
            lines++;
        }
        content++;
    }

    content = p_content;

    if ((rows + content_idx) > lines) {
        progress = 100;
    } else {
        progress = (float)(rows + content_idx) / (float)lines * 100;
    }

    while (ch != KEY_F(3)) {
        wclear(window);
        mvwprintw(window, posX, posY, "%s", content);
        mvwprintw(parent_window, 0, progressY, "%.0f%%", progress);
        wrefresh(window);
        wrefresh(parent_window);

        ch = wgetch(window);

        if (ch == KEY_DOWN) {
            if (lines - content_idx > rows) {
                while (*content != '\n' && *content != '\0') {
                    content++;
                }
                if (*content == '\n') {
                    content++;
                }
                content_idx++;
            }
        }

        if (ch == KEY_UP) {
            if (content != p_content) {
                content--;
                do {
                    content--;
                } while (*content != '\n' && content != p_content);
                
                if (content != p_content) {
                    content++;
                }
                
                content_idx--;
            }
        }
    }
}