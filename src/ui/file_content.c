#include <ncurses.h>

void create_content_window(char * content) {
    WINDOW * outer;
    WINDOW * inner;
    int posX = 0, posY = 0, ch = 0, lines = 0, content_idx = 0, consumed_chars = 0;
    int progressX = 0, progressY = 0;
    float progress = 0;
    int  inner_height, inner_width, outer_height, outer_width;
    char * PContent = content;

    outer_height = LINES - 5;
    outer_width = COLS - 3;

    inner_height = outer_height - 3;
    inner_width = outer_width - 3;

    progressY = inner_width - 5;

    outer = newwin(outer_height, outer_width, 1, 2);
    inner =  newwin(inner_height, inner_width, 2, 3);

    keypad(inner, TRUE);
    wbkgdset(outer, COLOR_PAIR(1));
    wclear(outer);
    box(outer, 0, 0);
    box(inner, 0, 0);
    wrefresh(outer);

    wbkgdset(inner, COLOR_PAIR(4));
    wclear(inner);
    wrefresh(inner);
    while (*content != '\0') {
        if (*content == '\n') {
            lines++;
        }
        content++;
    }

    content = PContent;
    while (ch != KEY_F(3)) {
        if ((inner_height + content_idx) > lines) {
            progress = 100;
        } else {
            progress = (float)(inner_height + content_idx) / (float)lines * 100;
        }
        wclear(inner);
        mvwprintw(inner, posX, posY, "%s", content);
        mvwprintw(outer, 0, progressY, "%.0f%%", progress);
        wrefresh(inner);
        wrefresh(outer);

        ch = wgetch(inner);

        if (ch == KEY_DOWN) {
            if (lines - content_idx > inner_height) {
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
            if (content != PContent) {
                content--;
                do {
                    content--;
                } while (*content != '\n' && content != PContent);
                
                if (content != PContent) {
                    content++;
                }
                
                content_idx--;
            }
        }
    }
    delwin(inner);
    delwin(outer);
}