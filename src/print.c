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
    int file_so_far = 1;

    for (int col = 0; col < table->cols; col++) {
        table->max_col_size[col] = 0;

        for (int row = 0; row < table->rows; row++) {
            // printf("For row %d, col %d, str = %s\n", row,col, table->table[row][col]);
            if (1) {
                int len = mx_strlen(table->table[row][col]);
                // printf("For row %d, col %d, len = %d\n", row, col, len);
                if (len > table->max_col_size[col])
                    table->max_col_size[col] = len;
            }
            file_so_far++;
        }
    }
}

//allocates string table of given size
static t_table *allocate_table(int rows, int cols) {
    t_table *table = malloc(sizeof(t_table));

    table->rows = rows;
    table->cols = cols;
        //allocate max_col_size arrat
    table->max_col_size = malloc((cols) * sizeof(int));
        //allocate 2-D string array
    table->table = malloc(table->rows * sizeof(char**));
    for (int i = 0; i < table->rows; i++) {
        table->table[i] = malloc(table->cols * sizeof(char*));
    }
        //initialize table with NULLs
    for (int row = 0; row < table->rows; row++) {
        for (int col = 0; col < table->cols; col++) {
            table->table[row][col] = NULL;
    }
}
    return table;
}

//prints table
static void print_table(t_table *table) {
    int file_so_far = 1;
    get_max_width(table);
    for (int row = 0; row < table->rows; row++) {
        for (int col = 0; col < table->cols; col++) {
            if (table->table[row][col] != NULL) {
                mx_printstr(table->table[row][col]);
                if (col + 1 < table->cols)
                    if (table->table[row][col+1] != NULL)
                        print_tab(table->max_col_size[col], table->table[row][col]);
            }
        file_so_far++;
        }
    mx_printchar('\n');
    }
}

//gets filename from file node
char *mx_get_filename(t_file *file) {
    char *filename = mx_strdup(file->name);
    return filename;
}

//fill table with given shototam
static void fill_table(t_table *table, t_file *files) {
    t_file *file = files;
        //iterate over list
    int row_so_far = 0, col_so_far = 0;
    while (file != NULL) {
        //get file name
        char *filename = mx_get_filename(file);
        // printf("At row %d, col %d, filename: %s\n", row_so_far, col_so_far, filename);
        table->table[row_so_far][col_so_far] = filename;
        row_so_far++;
        //go to next column
        if(row_so_far >= table->rows) {
            col_so_far++;
            row_so_far = 0;
        }
        file = file->next;
    }
}

//prints directory contents
void mx_print_dir(t_file *dir, t_flags *flags) {
        //get rows and columns
    int rows = 0, cols = 0;
    mx_get_rows_cols(&rows, &cols, dir->level, flags);
        //allocate table
    t_table *table = allocate_table(rows, cols);
        //fill table
    fill_table(table, dir->level);
        //print table
    print_table(table);
} 
