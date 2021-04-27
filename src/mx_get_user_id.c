#include "uls.h"

char *mx_get_user_id(t_file *fist, t_flags *flags) {
    fist->pwd = getpwuid(fist->filestat.st_uid);
    
    if (flags->n) 
        return mx_itoa(fist->filestat.st_uid);
    else if (flags->l)
        return fist->pwd->pw_name;
    return NULL;
}
