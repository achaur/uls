#include "uls.h"

/*--- PRINT FLAGS TO IMPLEMENT ---
* -l : Print with long listing
* -a : print all hidden files (starts with .)
* -A : print all hidden files, but do not print ',' and '..'
*       which are directory references
* -G : in long listing, do not print group
* -h : print size with K, M, G etc.
* -i : print index number (stat.st_ino)
* -n : same as -l, but print group and user IDs instead of names
* -p : append / symbol to directories
* -1 : one file per file
-----------------------------*/

/*--- TO-DO:
    - function which prints table to terminal                   +
    - function which fill data into table (according to flags)
    - function which calculates space intendation               +
    - function which allocates table                            +
    - function to fill max_col_width                            +
--------------------------*/

//prints needed amount of whitespaces for pretty output
void print_tab(int max_size, char *str) {
    int spaces = max_size - mx_strlen(str) + TAB_SIZE;

    while (spaces-- > 0)
        mx_printchar(' ');
}

//calculates max column width for every column in the table
void get_max_width(t_table *table) {
    for (int col = 0; col < table->cols; col++) {
        table->max_col_size[col] = 0;
        for (int row = 0; row < table->rows; row++) {
            int len = mx_strlen(table->table[row][col]);
            if (len > table->max_col_size[col])
                table->max_col_size[col] = len;
        }
    }
}

//allocates string table of given size
t_table *mx_allocate_table(int rows, int cols) {
    t_table *table = malloc(sizeof(t_table));

    table->rows = rows;
    table->cols = cols;
        //allocate max_col_size arrat
    table->max_col_size = malloc((cols - 1) * sizeof(int));
        //allocate 2-D string array
    table->table = malloc(table->rows * sizeof(char**));
    for (int i = 0; i < table->rows; i++) {
        table->table[i] = malloc(table->cols * sizeof(char*));
    }
    return table;
}

//prints table
void mx_print_table(t_table *table) {
    get_max_width(table);
    for (int row = 0; row < table->rows; row++) {
        for (int col = 0; col < table->cols; col++) {
            mx_printstr(table->table[row][col]);
            print_tab(table->max_col_size[col], table->table[row][col]);
        }
    mx_printchar('\n');
    }
}
