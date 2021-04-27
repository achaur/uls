#include "uls.h"

char *mx_get_index_number(t_file *fist) {
    stat(fist->name, &fist->filestat);
    return mx_itoa(fist->filestat.st_ino);
}
