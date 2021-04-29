#include "uls.h"

static int mx_round_number(double size_of_file) {//function to round file's size
    bool msb = 0;
    int integer_num = (size_of_file * 10);

    msb = integer_num % 10 >= 5;
    integer_num /= 10;
    integer_num += msb;
    return integer_num;
}

char *mx_get_size(t_file *fist, t_flags *flags) {
    char *sizes[] = {"B", "K", "M", "G", "T", "P", "E", "Z", "Y"};
    int count = 0;
    char *res = NULL;
    double size_of_file = fist->filestat.st_size;
    char *number = NULL;

    if (flags->l && !flags->h) {
        res = mx_itoa(size_of_file);
    }
    else if (flags->l && flags->h) {
        if (size_of_file < 1024) {
            // res = mx_strjoin(mx_itoa(size_of_file), "B");//macos ls-lh display
            res = mx_itoa(size_of_file);//Ubuntu ls -lh dispay
        }
        else {
            //counting file's size
            while (size_of_file > 1024) {
                size_of_file /= 1024;
                count++;
            }
            if (size_of_file < 10) {
                int round = mx_round_number(size_of_file * 10);
                char *whole_number = mx_itoa(round / 10);
                char *fraction = mx_itoa(round % 10);
                char *number_with_dot = mx_strjoin(whole_number, ".");
                number = mx_strjoin(number_with_dot, fraction);
                res = mx_strjoin(number, sizes[count]);
                free(whole_number);
                free(fraction);
                free(number_with_dot);
                free(number);
            }
            else {
                int round = mx_round_number(size_of_file);
                number = mx_itoa(round);
                res = mx_strjoin(number, sizes[count]);
                free(number);
            }
        }
    }
    return res;
}
