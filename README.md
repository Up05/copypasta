# copypasta
TUI for easily copying preset unicode text (Linux only) 

Items work similar to table cells, they have an x coordinate (a-z) and a y coordinate (0-9).  
*You may think of it as Excel/localc: `=SUM(A1:G5)` except lowercase*

Special shortcuts:  
  - `&`: adds a new category and puts the user into input mode (twice, first 1 char then until `Enter`)  
  - `+`: adds a new item and puts user into input mode (until enter) then opens (by default) `nvim /tmp/ulti-copypasta-recent-body`  
  - `ctrl + C`: to exit btw

Basic configuration can be done within `config.h`  
Program may be compiled using `compile.sh` (or just `gcc *.c -lncursesw`)

![copypasta-demo](https://github.com/user-attachments/assets/8270143c-e2b1-41da-80c7-e566ad3081ac)
*"`q` to quit" has been removed.*
