#include "uls.h"

int mx_get_user_id(t_file *file, t_flags *flags) {
    int buf = file->filestat.st_uid;
    printf("%d\n", buf);
    return buf;
}
