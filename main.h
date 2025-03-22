#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <curses.h>

#include "config.h"
// #include "main.h"

typedef char* str;
typedef unsigned char byte;
typedef unsigned int  u32;

#define len_of(ARRAY) (sizeof(ARRAY) / sizeof(*(ARRAY)))
#define foreach(I, ARRAY) for(int I = 0; I < len_of(ARRAY); I ++)
#define ADDF_BUFFER_SIZE 128
#define addfs(SIZE, FMT, ...) { char BUF[SIZE]; snprintf(BUF, sizeof BUF, FMT, __VA_ARGS__); addstr(BUF); }
#define addf(FMT, ...) addfs(128, FMT, __VA_ARGS__)
#define assertf(EXPR, FMT, ...) if(!(EXPR)) { addfs(1024, "[ASSERTION] " FMT, __VA_ARGS__); exit(1); }
#define min(a, b) ( (a)*((a) <= (b))  +  (b)*((a)  > (b)) )
#define max(a, b) ( (a)*((a)  > (b))  +  (b)*((a) <= (b)) )

#define LETTER_COUNT ('Z' - 'A' + 1) // 26
#define COLORS_HIGHLIGHTED 1

void u_move(int x, int y);
void u_return(); 
str repeat(char c, int n); 
int u_x(); 
int u_y(); 
void u_refresh();
void highlight_col(int x, int from);
void highlight_row(int y, int from); 

typedef struct {
    str title;
    str text;
} Item;

typedef struct {
    str  name;
    char key;
    Item items[127];
} Category;

str cat2(str a, str b);
int index_char(str s, char c);
str slice(str s, int from, int to);
str del_esc_chars(str s);
str escape(str s);
int rune_size(u32 rune);
int rune_count(str s);
u32 first_rune(str s); 

extern Category categories[32];
extern int cur_category;
extern int cur_row;
extern int cur_col;
extern int last_category_x;
extern int row_offsets[LETTER_COUNT];
extern int item_table[LETTER_COUNT][9];
extern int plus_item_col, plus_item_row;
extern int last_key;

Category make_category(str name, char key);
int add_category(str name, char key);
void draw_categories();
void draw_items();
void draw_last_key();
Item make_item(str title, str text);

void init_io();
void load_categories();
void copy(str text);
void make_category_file(str name, char key); 
bool handle_key(int key);
str clone_str(str s);
int fmt_highlight(bool on);
#endif
