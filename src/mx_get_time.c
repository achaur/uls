#include "uls.h"

char *my_strcpy(char *dst, const char *src) {//function to remove day, seconds, and year from the displayed time 
    int i = 4;
    int k = 0;

    for ( ; i < 16; i++, k++)
        dst[k] = src[i];
    dst[k] = '\0';
    return dst;
}

char *mx_get_time(t_file *fist, t_flags *flags) {
    char *tmp = (char *)malloc(sizeof(char)* (12 + 1));

    stat(fist->name, &fist->filestat);
    if (flags->l && !flags->t)
        return my_strcpy(tmp, ctime(&fist->filestat.st_mtime));
    else if (flags->l && flags->t) 
        return my_strcpy(tmp, ctime(&fist->filestat.st_atime));//display last access time 
    return NULL;
}
