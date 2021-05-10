#include "uls.h"

//check if directory is root
bool mx_is_root(const char *dir) {
    return (!mx_strcmp("..", dir) || !mx_strcmp(".", dir));
}

//check if directory is hidden directory
bool mx_is_hidden(const char *dir) {
    if (*dir == '.' && !mx_is_root(dir))
        return true;
    else
        return false;
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

//return available terminal width (in symbols)
int mx_get_term_width(void) {
    struct winsize w;
        //get terminal width
    ioctl(1, TIOCGWINSZ, &w);
    int term_width = w.ws_col;
    if (term_width == 0)
            //80 symbols by default (if failed to get width)
        term_width = 80;
    return term_width;
}

//prints total size of folder components
void mx_print_tot_size(t_file *dir, t_flags *flags) {
    int sum_so_far = 0;
    while (dir != NULL) {
        sum_so_far += dir->filestat.st_size / dir->filestat.st_blksize;
        if (dir->filestat.st_size % dir->filestat.st_blksize > 0)
            sum_so_far++;
        dir = dir->next;
    }
    sum_so_far *= 4;

    mx_printstr("total ");
    mx_printint(sum_so_far);
    if (flags->h)
        mx_printchar('K');
    mx_printchar('\n');
}

//function which returns link in form "src" -> "dst"
char *mx_get_link(char *fullpath, char *name) {
        //create buffer to read link (max filename(256) + '\0')
    char *buff = mx_strnew(257);
    readlink(fullpath, buff, 257);
        //append -> 
    char *temp = mx_strjoin(name, " -> ");
        //append destination
    char *res = mx_strjoin(temp, buff);
    //free all used memory
    mx_strdel(&buff);
    mx_strdel(&temp);
    return res;
}
