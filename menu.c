#include "main.h"

Category categories[32] = {};
int cur_category = 0;
int cur_row = -1;
int cur_col = -1;
int last_category_x = 0;

int plus_item_row = 0;
int plus_item_col = 0;

int item_table[LETTER_COUNT][9] = {};
int row_offsets[LETTER_COUNT] = {};

Item make_item(str title, str text) { return (Item) { title, text }; }
Category make_category(str name, char key) { return (Category) { name, key }; }

void draw_categories() {/*{{{*/
    u_move(0, 0);
    foreach(i, categories) {
        Category c = categories[i];
        if(c.name == 0) break;
        fmt_highlight(i == cur_category);
        addf("[%c]%s", c.key, c.name);
        if(i == cur_category) fmt_highlight(false);
        addstr(repeat(' ', SPACING_X));
        last_category_x += 5 + rune_count(c.name);
    }
    addstr("[&]Add category  ");
    u_return();
}/*}}}*/

int add_category(str name, char key) {/*{{{*/
    foreach(i, categories) {
        if(categories[i].name == 0) {
            make_category_file(name, key);
            categories[i].name = name;
            categories[i].key  = key;
            cur_category = i;
            return i;
        }
        // strcmp is a bit stupid, it returns 0 if a == b
        if(!strcmp(categories[i].name, name)) {
            // Should also warn here
            return -1;
        }
    } 
    return -1;
}/*}}}*/

void draw_items() {/*{{{*/
    Category* c = categories + cur_category;

    int longest_title = 1;
    foreach(i, c->items) {
        Item item = c->items[i];
        if(item.title == 0) break;
        if(rune_count(item.title) > longest_title) longest_title = rune_count(item.title);
    }
    longest_title += SPACING_X;
    
    int ppx, ppy;
    getyx(curscr, ppy, ppx);

    int i_this_line = 0;
    int y = START_Y;
    foreach(i, c->items) {
        Item item = c->items[i];
        
        int x = START_X + longest_title * i_this_line;

        if(x + longest_title >= COLS - 1 || i_this_line >= LETTER_COUNT) { y += SPACING_Y; i_this_line = 0; x = START_X; }
        u_move(x, y);

        row_offsets[i_this_line] = x;
        if(item.title == 0) {
            plus_item_col = i_this_line;
            plus_item_row = (y - START_Y) / SPACING_Y;
            addstr("[+]");
            break;
        }
        addstr(item.title);
        item_table[i_this_line][(y - START_Y) / SPACING_Y] = i;

        i_this_line ++;
    }

    i_this_line = 0;
    for(int x = START_X; x + longest_title < COLS && i_this_line < LETTER_COUNT; x += longest_title) {
        u_move(x, 2);
        addf("[%c]", i_this_line + 'a');
        i_this_line ++;
    }

    for(int y = START_X; y < min(22, LINES - 8); y += SPACING_Y) {
        u_move(0, y);
        addf("[%c]", (y - START_Y) / SPACING_Y + '1');
    }
    
    u_move(ppx, ppy);
}/*}}}*/

void highlight_col(int x, int from) {/*{{{*/
    u_move(u_x(), u_y());
    for(int i = from; i < LINES; i ++) {
        move(i, x);
        chgat(1, A_STANDOUT, 0, 0);
    }
    u_return();
}/*}}}*/

void highlight_row(int y, int from) {/*{{{*/
    u_move(from, y);
    chgat(-1, A_STANDOUT, 0, 0);
    u_return();
}/*}}}*/

void draw_help() {
    u_move(0, min(24, LINES - 8));
    addstr("  in [?] ? is a key shortcut.\n");
    addstr("  A..Z = categories, a..z = column, 1..9 = row, '&' and '+' = adding\n");
    addstr("  copy cmd: '" COPY_COMMAND "' (defined in config.h)\n");
    addstr("  edit cmd: '" EDIT_COMMAND "' (defined in config.h)\n");
    addstr("  category contents may be edited in '~/.config/ulti/copypasta/**'\n");
    addstr("    syntax: `KEY\\n({TITLE}\\n{TEXT2COPY})*` '*' = repeated 0 or more times, '( )' = group");
    u_return();
}

void draw_last_key() {
    u_move(COLS - 20, LINES - 1);
    addf("%c    ", last_key);
    u_return();
}

void u_refresh() {
    clear();
    u_move(0, 0);
    last_category_x = 0;
    draw_help();
    draw_categories();
    draw_items();
    draw_last_key();
    refresh();
    u_return();
}

