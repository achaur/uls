#include "uls.h"

char *mx_get_group_id(t_file *fist, t_flags *flags) {
    fist->pwd = getpwuid(fist->filestat.st_uid);
    fist->grp = getgrgid(fist->pwd->pw_gid);

    if (flags->n) 
        return mx_itoa(fist->pwd->pw_gid);
    else if (flags->l)
        return fist->grp->gr_name;
    return NULL;
}
