
// copy to the clipboard, the TEMP_FILE_PATH is used for fwrite too
#define TEMP_FILE_PATH "/tmp/ulti-copypasta-recent"
#define CLIPBOARD_MANAGER "xsel -b"
#define COPY_COMMAND "cat " TEMP_FILE_PATH " | " CLIPBOARD_MANAGER

// Btw, 1 last '\n' will get automatically removed
#define ITEM_BODY_FILE "/tmp/ulti-copypasta-recent-body"
#define ITEM_BODY_EDITOR "nvim"
#define EDIT_COMMAND ITEM_BODY_EDITOR " " ITEM_BODY_FILE

#define MAX_FILE_SIZE 1024*1024

#define START_X 4  // column at which the items will start to be listed
#define START_Y 4  // line ..^

#define SPACING_Y 2  // number of lines 1 row of item will take up. So, if you want 2 empty lines between [1] and [2], #define SPACING_Y 3  
#define SPACING_X 2  // number of ' ' between category and item names


