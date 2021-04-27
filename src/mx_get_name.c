#include "uls.h"

char *mx_get_name(t_file *fist, t_flags *flags) {
    stat(fist->name, &fist->filestat);

    if (!flags->F) 
        return fist->name;
    else if (flags->l && flags->F) {
        switch (fist->filestat.st_mode & S_IFMT) {
            case S_IFDIR:                         //check if the file is a directory
                return mx_strjoin(fist->name, "/");
            case S_IXUSR:                         //check if the file is an executable file
                return mx_strjoin(fist->name, "*");
            case S_IFIFO:                         //check if the file is a pipe
                return mx_strjoin(fist->name, "|");
            case S_IFLNK:                         //check if the file is a symbolic link
                return mx_strjoin(fist->name, "@");
            case MX_IFSOCK:                        //check if the file is a socket
                return mx_strjoin(fist->name, "=");
            // case MX_                               //check if the file is a door????
            //     return mx_strjoin(fist->name, ">");
            default:
                return fist->name;
        }
    }
    return NULL;
}
