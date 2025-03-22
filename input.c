#include "main.h"
#include <unistd.h>

int last_key = ' ';

void select_item() {
    // highlight -> addstr -> set cur_col & cur_row = -1
    int x = row_offsets[cur_row];
    int y = cur_col*SPACING_Y + START_Y;
    int i = item_table[cur_row][cur_col];
    if((cur_row != 0 || cur_col != 0) && i == 0) goto reset;
    
    Item* item = categories[cur_category].items + i;
    if(item->title == 0) goto reset;

    fmt_highlight(true);
    u_move(x, y);    
    addstr(item->title);
    u_return();
    fmt_highlight(false);

    copy(item->text);
    
    refresh();
    napms(200);
    u_refresh();

reset:
    cur_col = -1;
    cur_row = -1;
}

bool handle_key(int key) {
    last_key = key;
    draw_last_key();

    if(key >= 'a' && key <= 'z') {
        cur_row = key - 'a';
        u_refresh();
        if(cur_col != -1) select_item();
        else highlight_col(row_offsets[cur_row], 1);
    }

    if(key >= '1' && key <= '9') {
        cur_col = key - '1';
        u_refresh();
        if(cur_row != -1) select_item();
        else highlight_row(cur_col*SPACING_Y + START_Y, 0);
    }

    switch(key) {
    case 27: endwin(); exit(0); // escape key
    case '&':
        u_move(last_category_x, 0);
        addstr(repeat(' ', 20));
        move(0, last_category_x);
        echo();
        addch('['); char key = (char) getch(); addch(']');
        str name = malloc(64); getnstr(name, 64);
        noecho();
        add_category(name, key);
        u_return();
        u_refresh();
        break;
    case '+':
        u_move(row_offsets[plus_item_col], plus_item_row * SPACING_Y + START_Y);
        addstr("   ");
        move(plus_item_row * SPACING_Y + START_Y, row_offsets[plus_item_col]);
        echo();
        str title = malloc(64); 
        getnstr(title, 64);
        noecho();

        str body; {
            system(EDIT_COMMAND);
            FILE* f = fopen(ITEM_BODY_FILE, "rb");
            char buf[MAX_FILE_SIZE] = { };
            fread(buf, 1, sizeof buf, f);
            fclose(f);
            body = clone_str(buf);
        }

        foreach(i, categories[cur_category].items) {
            Item* item = categories[cur_category].items + i;
            if(item->title == 0) {
                *item = make_item(title, body);
                break;
            }
        }

        str escaped_body  = escape(body);
        str escaped_title = escape(title);
        for(int i = 0; i < strlen(body); i ++) {
            addf("%x ", escaped_body[i] & 0xff);
        }

        FILE* f = fopen(categories[cur_category].name, "a");
        fprintf(f, "{%s}\n{%s}\n", escaped_title, escaped_body);
        fclose(f);
        free(escaped_body); free(escaped_title);

        u_return();
        u_refresh();
        break;
    }

    foreach(i, categories) {
        if(categories[i].name == 0) break;
        if(categories[i].key == key) {
            cur_category = i;
            cur_row = -1;
            cur_col = -1;
            u_refresh();
        }
    }

    return true;
    // return key != 'q';
}
