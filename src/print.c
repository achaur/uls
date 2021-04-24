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
    - function which calculates space intendation
    - function which allocates table                            +
--------------------------*/

void mx_print_table(t_table *table) {
    for (int col = 0; col < table->cols; col++) {
        for (int row = 0; row < table->rows; row++) {
            mx_printstr(table->table[row][col]);
            //add space here
            mx_printstr("  ");
        }
    mx_printchar('\n');
    }
}
