#include "uls.h"

//check if directory is root
bool mx_is_root(const char *dir) {
    return (!mx_strcmp("..", dir) || !mx_strcmp(".", dir));
}

//form full path string
char *mx_get_fullpath(const char *path, const char *file) {
    char *temp = mx_strjoin(path, "/");
    char *fullpath = mx_strjoin(temp, file);
    mx_strdel(&temp);
    return fullpath;
}
