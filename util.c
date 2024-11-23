#include "main.h"

str cat2(str a, str b) {
    int len_a = strlen(a), len_b = strlen(b);
    int len = len_a + len_b + 1;
    char* buf = malloc(len);
    memcpy(buf,         a, len_a);
    memcpy(buf + len_a, b, len_b);
    buf[len - 1] = 0;
    return buf;
}

// Looks for UNESCAPED char, escape character is: '\'
int index_char(str s, char c) {
    int i = 0;
    bool escaped = false;
    while(s[i] != 0) {
        if(escaped) escaped = false;
        else {
            if(s[i] == '\\') escaped = true;
            if(s[i] == c) return i;
        }
        i ++;
    }
    return -1;
}

// Your slices wrap, my slices copy. We are not the same.
str slice(str s, int from, int to) {
    int span = to - from;
    str buf = malloc(span + 1);
    s += from;
    memcpy(buf, s, span);
    buf[span] = 0;
    return buf;
}

str del_esc_chars(str s) {
    int len = strlen(s);
    str buf = malloc(len + 1);
    int j = 0;
    bool escaped = false;
    for(int i = 0; i < len; i ++) {
        if(escaped) escaped = false;
        else if(s[i] == '\\') {
            continue;
            escaped = true;
        }
        buf[j] = s[i];
        j ++;
    }
    buf[len] = 0;
    return buf;
}

str escape(str s) {
    int len = strlen(s);
    str buf = malloc(len * 2 + 1); // worst case 
    // memset(buf, 0, len * 2 + 1);

    int j = 0;
    for(int i = 0; i < strlen(s); i ++) {
        if(s[i] == '\\' || s[i] == '{') {
            buf[j] = '\\';
            buf[j + 1] = s[i];
            j += 2;
        } else {
            buf[j] = s[i];
            j ++;
        }
    }
    if(buf[j - 1] == 0xA) buf[j - 1] = 0;
    buf[j] = 0;
    return buf;
}

int rune_size(u32 rune) {
         if(rune < 0x00007F) return 1;
    else if(rune < 0x0007FF) return 2;
    else if(rune < 0x00FFFF) return 3;
    else if(rune < 0x10FFFF) return 4;
    addf("Invalid rune found: '%x'!", rune);
}

int concat_and_flip_endian(byte* bytes, int len) {
    int out = 0;
    if(len > 0) out |= bytes[0];
    if(len > 1) out |= bytes[1] >> 8;
    if(len > 2) out |= bytes[2] >> 16;
    if(len > 3) out |= bytes[3] >> 24;
    return out;
}

int rune_count(str s) {
    int runes = 0;
    int len = strlen(s);
    int i = 0;
    while(i < len) {
        u32 rune = concat_and_flip_endian(s + i, (len - i) % 4);
        int size = rune_size(rune);
        i += size;
        runes ++;
    }
    return runes;
}

str repeat(char c, int n) {
    str s = malloc(n + 1);
    memset(s, c, n);
    s[n] = 0;
    return s;
}

str clone_str(str s) {
    int len = strlen(s);
    str new = malloc(len + 1);
    memcpy(new, s, len);
    new[len] = 0;
    return new;
}

// CURSES EXTENSIONS

int u_x() {
    int x, y;
    getyx(curscr, y, x);
    return x;
}

int u_y() {
    int x, y;
    getyx(curscr, y, x);
    return y;
}

int px = 0, py = 0;
void u_move(int x, int y) {/*{{{*/
    assertf(x >= 0 && x < COLS,  "Tried to move out of bounds! x = %d\n", x);
    assertf(y >= 0 && y < LINES, "Tried to move out of bounds! y = %d\n", y);
    getyx(curscr, py, px);
    move(y, x);
}/*}}}*/

void u_return() { move(py, px); }



