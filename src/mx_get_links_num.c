#include "uls.h"

char *mx_get_links_num(t_file *fist) {
    stat(fist->name, &fist->filestat);
    return mx_itoa(fist->filestat.st_nlink);
}
