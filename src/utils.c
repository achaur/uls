#include "uls.h"

//check if directory is root
bool mx_is_root(const char *dir) {
    return (!mx_strcmp("..", dir) || !mx_strcmp(".", dir));
}

//form full path string
char *mx_get_fullpath(const char *name, const char *path) {
    char *fullpath;

        //if path is empty (at first entry), do not add '/'
    if (path == NULL)
        fullpath = mx_strdup(name);
    else {
        char *temp = mx_strjoin(path, "/");
        fullpath = mx_strjoin(temp, name);
        mx_strdel(&temp);
    }
    return fullpath;
}

