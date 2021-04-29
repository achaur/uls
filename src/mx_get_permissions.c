#include "uls.h"

static void mx_first_symbol(t_file *fist, char *buf) {
    if (S_ISDIR(fist->filestat.st_mode)) //check if it is a directory
        buf[0] = 'd';
    if ((fist->filestat.st_mode & S_IFIFO) == S_IFIFO)//check if it is a fifo/chanel
        buf[0] = 'p';
    if ((fist->filestat.st_mode & S_IFCHR) == S_IFCHR) {//check if it is a symbolic device
        buf[0] = 'c';
    }
    if ((fist->filestat.st_mode & S_IFBLK) == S_IFBLK) {//check if it is a block
        buf[0] = 'b';
    }
    if ((fist->filestat.st_mode & S_IFREG) == S_IFREG)//check if it is a usual file
        buf[0] = '-';
    if (S_ISLNK(fist->filestat.st_mode)) { //check if it is a symbolic link
        buf[0] = 'l';
    }
    if ((fist->filestat.st_mode & MX_IFSOCK) == MX_IFSOCK)//check if it is a socket
        buf[0] = 's';
}

static void mx_other_symbols(t_file *fist, char *buf) {
    if ((fist->filestat.st_mode & S_IRUSR) == S_IRUSR)//check if user has a right to read
        buf[1] = 'r';
    if ((fist->filestat.st_mode & S_IWUSR) == S_IWUSR)//check if user has a right to write
        buf[2] = 'w';
    if ((fist->filestat.st_mode & S_IXUSR) == S_IXUSR)//check if user has a right to execute
        buf[3] = 'x';
    if ((fist->filestat.st_mode & S_ISUID) == S_ISUID) 
        buf[3] = (buf[3] = 'x') ? 's' : 'S';
    if ((fist->filestat.st_mode & S_IRGRP) == S_IRGRP)//check if the group has the right to read
        buf[4] = 'r';
    if ((fist->filestat.st_mode & S_IWGRP) == S_IWGRP)//check if the group has the right to write
        buf[5] = 'w';
}

static void mx_other_symbols2(t_file *fist, char *buf) {
    if ((fist->filestat.st_mode & S_IXGRP) == S_IXGRP)//check if the group has the right to execute
        buf[6] = 'x';
    if ((fist->filestat.st_mode & S_ISGID) == S_ISGID)
        buf[6] = (buf[6] = 'x') ? 's' : 'S';
    if ((fist->filestat.st_mode & S_IROTH) == S_IROTH)//check if others have the right to execute
        buf[7] = 'r';
    if ((fist->filestat.st_mode & S_IWOTH) == S_IWOTH)//check if the others have the right to execute
        buf[8] = 'w';
    if ((fist->filestat.st_mode & S_IXOTH) == S_IXOTH)//check if the others have the right to execute
        buf[9] = 'x';
    if ((fist->filestat.st_mode & S_ISVTX) == S_ISVTX)
        buf[9] = (buf[9] = 'x') ? 't' : 'T';
}

char *mx_get_permissions(t_file *fist) {
    char *buf = mx_strnew(11);
    
    for (int i = 0; i < 10; i++)
        buf[i] = '-';
    mx_first_symbol(fist, buf);//type of the file
    mx_other_symbols(fist, buf);
    mx_other_symbols2(fist, buf);
    buf[10] = '\0';
    // printf("%s\n", buf);
    return buf;
}
