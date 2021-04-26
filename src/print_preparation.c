#include "uls.h"

//function which gets amout of files in the list
int mx_get_filesnum(t_file *dir) {
    int res = 0;
    t_file *list = dir;

    while (list != NULL) {
        res++;
        list = list->next;
    }

    return res;
}

//calculates number of rows based of number of files and columns
int mx_get_rows(int cols, int filesnum) {
    //number of rows = number of files / nubmer of cols
    //and if nofiles % nocols > 0, rows + 1
    int rows = filesnum / cols;
    if (filesnum % cols)
        rows++;
    
    return rows;
}

//iteratively calculates number of columns for -C flag
int mx_get_cols(t_file *dir) {
    t_file *list = dir;
    struct winsize w;
    
    //get filesnum
    int filesnum = mx_get_filesnum(dir);
    //allocate array of ints which are name lengths for each file
    int *width = malloc(sizeof(int) * filesnum);
    for (int i = 0; i < filesnum; i++) {
        width[i] = mx_strlen(list->name);
        list = list->next;
    }

    //get terminal width
    ioctl(1, TIOCGWINSZ, &w);
    int term_width = w.ws_col;
    if (term_width == 0)
        term_width = 80;

    printf("Number of files: %d\n", filesnum);
    printf("Terminal width: %d\n\n", term_width);

    for (int i = 0; i < filesnum; i++)
        printf("No: %d,\twidth: %d\n", i, width[i]);

    //iteratively calculate if columns fits into terminal

    //check if everything can be fitted in one row
    int total_width = 0;
    for (int file_so_far = 0; file_so_far < filesnum; file_so_far++) {
        total_width += width[file_so_far];
    }
    printf("Total width in one column: %d\n", total_width);
    if (total_width <= term_width)
        return filesnum;

    int cols_so_far = 1;
    for ( ; cols_so_far < filesnum; cols_so_far++) {
        int max_width = 0, file_so_far = 0;
        int rows_so_far = mx_get_rows(cols_so_far, filesnum);

        printf("At cols: %d\n", cols_so_far);
        printf("\tRows so far: %d\n", rows_so_far);

                //if more than one column can be left unfilled, break
        if (rows_so_far != 1 && cols_so_far != 1) {
            if ((rows_so_far * cols_so_far) % filesnum > rows_so_far) {

                printf("Max possible\n");

                cols_so_far--;
                break;
            }
        }

        for (int i = 1; i <= cols_so_far; i++) {
            int max_so_far = 0;

            printf ("\t\tFor i=%d\n", i);

            for ( ; file_so_far < rows_so_far * i; file_so_far++) {

                printf("\t\t\tFor file_so_far=%d\n", file_so_far);

                if (file_so_far >= filesnum)
                    break;
                if (width[file_so_far] > max_so_far)
                    max_so_far = width[file_so_far];

                printf("\t\t\tmax_fo_far=%d\n", max_so_far);
            }
            max_width += max_so_far;

            printf("\t\tmax_width=%d\n", max_width);

        }
        if (max_width > term_width) {

            printf("Max width reached.\n");

            cols_so_far--;
            break;
        }
    }
    return cols_so_far;
    }

//calculates number of rows and columns according to flags
void mx_get_rows_cols(int *rows, int *cols, t_file *dir, t_flags *flags) {
    //if there is -l or -n flag, calculate number of columns according to flags
    if (flags->l && flags->n) {
        if (flags->G)
            *cols = 6;
        else
            *cols = 7;
        *rows = mx_get_filesnum(dir);
    } else if (flags->one) {
    //if there is -1 flag, one column
        *cols = 1;
        *rows = mx_get_filesnum(dir);
    } else {
    //if -C flag or no other flags, calculate iteratively for terminal width

    }
}
