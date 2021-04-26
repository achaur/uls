#include "uls.h"

static void mx_first_symbol(t_file *file, char *buf) {
    if ((file->filestat.st_mode & MX_IFDIR) == MX_IFDIR)//check if it is a directory
        buf[0] = 'd';
    if ((file->filestat.st_mode & MX_IFIFO) == MX_IFIFO)//check if it is a fifo/chanel
        buf[0] = 'p';
    if ((file->filestat.st_mode & MX_IFCHR) == MX_IFCHR) {//check if it is a symbolic device
        buf[0] = 'c';
    }
    if ((file->filestat.st_mode & MX_IFBLK) == MX_IFBLK) {//check if it is a block
        buf[0] = 'b';
    }
    if ((file->filestat.st_mode & MX_IFREG) == MX_IFREG)//check if it is a usual file
        buf[0] = '-';
    if ((file->filestat.st_mode & MX_IFLNK) == MX_IFLNK) {//check if it is a symbolic link
        buf[0] = 'l';
    }
    if ((file->filestat.st_mode & MX_IFSOCK) == MX_IFSOCK)//check if it is a socket
        buf[0] = 's';
}

static void mx_other_symbols(t_file *file, char *buf) {
    if ((file->filestat.st_mode & MX_IRUSR) == MX_IRUSR)//check if user has a right to read
        buf[1] = 'r';
    if ((file->filestat.st_mode & MX_IWUSR) == MX_IWUSR)//check if user has a right to write
        buf[2] = 'w';
    if ((file->filestat.st_mode & MX_IXUSR) == MX_IXUSR)//check if user has a right to execute
        buf[3] = 'x';
    if ((file->filestat.st_mode & MX_ISUID) == MX_ISUID) 
        buf[3] = (buf[3] = 'x') ? 's' : 'S';
    if ((file->filestat.st_mode & MX_IRGRP) == MX_IRGRP)//check if the group has the right to read
        buf[4] = 'r';
    if ((file->filestat.st_mode & MX_IWGRP) == MX_IWGRP)//check if the group has the right to write
        buf[5] = 'w';
}

static void mx_other_symbols2(t_file *file, char *buf) {
    if ((file->filestat.st_mode & MX_IXGRP) == MX_IXGRP)//check if the group has the right to execute
        buf[6] = 'x';
    if ((file->filestat.st_mode & MX_ISGID) == MX_ISGID)
        buf[6] = (buf[6] = 'x') ? 's' : 'S';
    if ((file->filestat.st_mode & MX_IROTH) == MX_IROTH)//check if others have the right to execute
        buf[7] = 'r';
    if ((file->filestat.st_mode & MX_IWOTH) == MX_IWOTH)//check if the others have the right to execute
        buf[8] = 'w';
    if ((file->filestat.st_mode & MX_IXOTH) == MX_IXOTH)//check if the others have the right to execute
        buf[9] = 'x';
    if ((file->filestat.st_mode & MX_ISVTX) == MX_ISVTX)
        buf[9] = (buf[9] = 'x') ? 't' : 'T';
}

char *mx_get_user_rights(t_file *file, t_flags *flags) {
    char *buf = mx_strnew(11);
    
    for (int i = 0; i < 10; i++)
        buf[i] = '-';
    mx_first_symbol(file, buf);//type of the file
    mx_other_symbols(file, buf);
    mx_other_symbols2(file, buf);
    // printf("%s\n", buf);
    return buf;
}