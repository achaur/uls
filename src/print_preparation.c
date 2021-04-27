#include "uls.h"

//function which gets amout of files in the list
static int get_filesnum(t_file *dir) {
    int res = 0;
    t_file *list = dir;

    while (list != NULL) {
        res++;
        list = list->next;
    }

    return res;
}

//calculates number of rows based of number of files and columns
//or number of columns base on number of files and rows
static int get_opposite(int cols, int filesnum) {
    //number of rows = number of files / nubmer of cols
    //and if nofiles % nocols > 0, rows + 1
    int rows = filesnum / cols;
    if (filesnum % cols)
        rows++;
    
    return rows;
}

//return nubmer of rows with which number of columns fits into window size
static int find_rows(int filesnum, int *width) {
    int term_width = mx_get_term_width();
        //iteratively calculate if columns fits into terminal
    int rows_so_far = 1;
    for ( ; rows_so_far < filesnum; rows_so_far++) {
        int max_width = 0, file_so_far = 0;
        int cols_so_far = get_opposite(rows_so_far, filesnum);
            //calculate max width based on how much columns there are
        for (int i = 1; i <= cols_so_far; i++) {
            int max_so_far = 0;
            for ( ; file_so_far < rows_so_far * i; file_so_far++) {
                if (file_so_far >= filesnum)
                    break;
                if (width[file_so_far] > max_so_far)
                    max_so_far = width[file_so_far];
            }
            max_width += max_so_far;
        }
            //if it fits into terminal window, break
        if (max_width < term_width)
            break;
    }
    return rows_so_far;
}

//iteratively calculates number of columns for -C flag
static int get_rows(t_file *dir) {
    t_file *list = dir;
        //get filesnum
    int filesnum = get_filesnum(dir);
        //allocate array of ints which are name lengths for each file
    int *width = malloc(sizeof(int) * filesnum);
    for (int i = 0; i < filesnum; i++) {
        width[i] = mx_strlen(list->name);
        list = list->next;
    }
    int rows = find_rows(filesnum, width);
        //free allocated memory
    free(width);
    width = NULL;
    return rows;
    }

//calculates number of rows and columns according to flags
void mx_get_rows_cols(int *rows, int *cols, int *filesnum, t_file *dir, t_flags *flags) {
        //if there is -l or -n flag, calculate number of columns according to flags
    if (flags->l || flags->n) {
        if (flags->G)
            *cols = 6;
        else
            *cols = 7;
        *rows = get_filesnum(dir);
        *filesnum = get_filesnum(dir);
    } else if (flags->one) {
        //if there is -1 flag, one column
        *cols = 1;
        *rows = get_filesnum(dir);
        *filesnum = get_filesnum(dir);
    } else {
        //if -C flag or no other flags, calculate iteratively for terminal width
        *rows = get_rows(dir);
        *cols = get_opposite(*rows, get_filesnum(dir));
        *filesnum = get_filesnum(dir);
    }
}
