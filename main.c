#include "main.h"

int colornum(int fg, int bg) {
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);
}

int main() {

    setlocale(LC_ALL, "");

    initscr();
    start_color();
    cbreak();  // disable line buffering (key press immediatelly read)
    noecho();  // do not display user input
    clear();
 
    init_io();
    load_categories();

    u_refresh();

    while(handle_key(getch()));
    endwin();
}
