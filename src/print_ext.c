#include "uls.h"

char *mx_get_index_number(t_file *file) {
    char *res = mx_strdup(mx_itoa(file->filestat.st_ino));
    return res;
}

char *mx_get_links_num(t_file *file) {
    char *res = mx_strdup(mx_itoa(file->filestat.st_nlink));
    return res;
}

char *mx_get_group_id(t_file *file, t_flags *flags) {
    struct group *group;
    char *grid = NULL;
    
    group = getgrgid(file->filestat.st_gid);
    if (flags->n) 
        grid = mx_strdup(mx_itoa(group->gr_gid));
    else
        grid = mx_strdup(group->gr_name);

    return grid;
}

char *mx_get_user_id(t_file *file, t_flags *flags) {
    struct passwd *user;
    char *uid = NULL;

    user = getpwuid(file->filestat.st_uid);
    if (flags->n) 
        uid = mx_strdup(mx_itoa(user->pw_uid));
    else
        uid = mx_strdup(user->pw_name);
    return uid;
}

char *mx_get_name(t_file *file, t_flags *flags) {
    char *name = NULL;
        //if flag p - append '/' to directories
    if(flags->p) {
            if(S_ISDIR(file->filestat.st_mode))
                name = mx_strjoin(file->name, "/");
            else
                name = mx_strdup(file->name);
            //if flag -F append classificator to everything
    } else if (flags->F) {
        switch (file->filestat.st_mode & S_IFMT) {
            case S_IFDIR:                         //check if the file is a directory
                name = mx_strjoin(file->name, "/");
                break;
            case S_IXUSR:                         //check if the file is an executable file
                name = mx_strjoin(file->name, "*");
                break;
            case S_IFIFO:                         //check if the file is a pipe
                name = mx_strjoin(file->name, "|");
                break;
            case S_IFLNK:                         //check if the file is a symbolic link
                name = mx_strjoin(file->name, "@");
                break;
            case MX_IFSOCK:                        //check if the file is a socket
                name = mx_strjoin(file->name, "=");
                break;
            // case MX_                               //check if the file is a door????
            //     return mx_strjoin(fist->name, ">");
            default:
                name = mx_strdup(file->name);
        }
            //if no that flags - just return name
    } else {
        name = mx_strdup(file->name);
    }
    return name;
}
