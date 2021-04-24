#include "uls.h"

char *mx_get_links_num(t_file *file, t_flags *flags) {
    unsigned short buf = file->filestat.st_nlink;
    return buf;
}
