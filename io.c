#include "main.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void init_io() {
    str HOME = cat2("/home/", getenv("USER"));
    mkdir(cat2(HOME, "/.config/ulti"), 0700);
    mkdir(cat2(HOME, "/.config/ulti/copypasta"), 0700);
    chdir(cat2(HOME, "/.config/ulti/copypasta"));
}

void load_category_from_file(str filename, int category_index) {/*{{{*/
    Category* c = categories + category_index;
    c->name = filename;

    FILE* file = fopen(filename, "r");
    char buf[MAX_FILE_SIZE] = { };
    fread(buf, 1, sizeof buf, file);
    
    int item = 0;
    int i = 0;

    if(buf[i] != '{' && buf[i] >= 'A' && buf[i] <= 'z') c->key = buf[i];
    i += index_char(buf, '{');
    if(i < 1) {
        fclose(file);
        return; // empty category
    }
    while(buf[i] == '{') {
        i ++;
        int j;

        j = index_char(buf + i, '}');
        assertf(j != -1, "Expected '}' in file '%s'!", filename);
        c->items[item].title = del_esc_chars(slice(buf + i, 0, j));
        i += j + 1;

        j = index_char(buf + i, '{');
        assertf(j != -1, "Expected second '{' in file '%s'!", filename);
        i += j + 1;
        
        j = index_char(buf + i, '}');
        assertf(j != -1, "Expected '}' in file '%s'!", filename);
        c->items[item].text = del_esc_chars(slice(buf + i, 0, j));
        i += j + 1;

        i += index_char(buf + i, '{');
        item ++;
    }

    fclose(file);
}/*}}}*/


void load_categories() {/*{{{*/
    DIR *dir = opendir(".");
    assertf(dir != 0, "Failed to open the '~/.config/ulti/copypasta directory!", "");
    struct dirent *ent;
    
    move(7, 2);
    readdir(dir); // skip '.'
    readdir(dir); // skip '..'
    int i = 0;
    while( (ent = readdir(dir)) != 0 ) {
        struct stat stats;
        stat(ent->d_name, &stats);
        load_category_from_file(clone_str(ent->d_name), i);
        i ++;
    }
    closedir(dir);

}/*}}}*/

void copy(str text) {
    FILE* file = fopen(TEMP_FILE_PATH, "w");
    fwrite(text, 1, strlen(text), file);
    fclose(file);
    system(COPY_COMMAND);
}

void make_category_file(str name, char key) {
    if(access(name, F_OK) == 0) return;
    FILE* f = fopen(name, "w");
    fprintf(f, "%c\n", key);
}








